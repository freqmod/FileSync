#include "serverconnection.h"
#include "filesync.pb.h"
#include "prototools.h"
#include <QtSql/QSqlQuery>
#include <QCryptographicHash>
namespace FileShare {
ServerConnection::ServerConnection(QObject *parent) :
    Connection(parent)
{
}
void ServerConnection::gotPacket(Packet *pkg){
    if(pkg->has_connect()){
        handleConnect(pkg);
    }
}

void ServerConnection::handleConnect(Packet *pkg){
    Connect connect = pkg->connect();
    QSqlQuery user_query;
    QSqlQuery client_query;
    user_query.prepare("SELECT id, root_repo, username, hashed_password, password_salt FROM user WHERE username=:username");
    user_query.bindValue("username", fromStdStringUtf8(connect.username()));
    user_query.exec();
    bool connection_invalid = false;
    if(user_query.size()==0){ // No users found
        connection_invalid = true;
    }else{
        user_query.next();
        QByteArray hashed_password = user_query.value(3).toString().toUtf8();
        QByteArray password_salt = user_query.value(4).toString().toUtf8();
        QCryptographicHash hasher(QCryptographicHash::Sha1);
        hasher.addData(password_salt);
        hasher.addData(fromStdString(connect.password()));
        if(hasher.result().toHex()!=hashed_password){
            connection_invalid = true;
        }
    }
    if(!connection_invalid){
        if(!connect.has_client_id()){//New client - make client entry

        }
        client_query.prepare("SELECT owning_user, name, last_updated FROM client WHERE id=:id AND owning_user=:uid");
        client_query.bindValue("uid", user_query.value(0));
        client_query.bindValue("id", fromStdString(connect.client_id()));
        client_query.exec();
        if(client_query.size()==0){ // No client found, most likely due not maching owning user
            connection_invalid = true;
        }
    }
    if(!connection_invalid){
        QSqlQuery repos_query;

        repos_query.prepare("SELECT id FROM RepoElement WHERE id=:repoid parent_repo=:repoid");
        repos_query.bindValue("repoid", user_query.value(1));
        repos_query.exec();
        QStringList repo_id_strings;
        int repo_ids[repos_query.size()];
        int i=0;
        while (repos_query.next()){
            repo_ids[i] = repos_query.value(0).toInt();
            repo_id_strings.append(QString("%d,").arg(repo_ids[i]));
            i++;
        }

        QSqlQuery files_query;
        //TODO: Check that mixing prepared replacements and verbatim parameters in same query works
        files_query.prepare(QString("SELECT FROM FileElement WHERE modified>:modified AND repo IN ")
                              .append("(")
                            .append(repo_id_strings.join(","))
                              .append(");"));
        files_query.bindValue("modified", client_query.value(2));
        files_query.exec();
        //TODO:Updated files have to be syncronized with client

    }
    if(connection_invalid){
        Packet response;
        InitializeClient *init = response.mutable_initclient();
        init->set_connection_succeeded(false);
        if(pkg->has_id())
            response.set_ack_id(pkg->id());
        sendPacket(&response);
    }
}

void ServerConnection::gotExtraData(Packet *pkg, QByteArray data){

}

}
