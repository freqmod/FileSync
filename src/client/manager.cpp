#include "manager.h"
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QCryptographicHash>
#include <QDateTime>
namespace FileShare {
Manager::Manager(QObject *parent) :
    QObject(parent)
{
}
QByteArray make_sha1_sum(QString filename){
    QCryptographicHash hasher(QCryptographicHash::Sha1);
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data;
        while(1){
            data = file.read(1024*1024);
            hasher.addData(data);
            if(data.length() < 1024*1024)
                break;
        }
        return hasher.result();
    }
    return QByteArray();
}

QList<QFileInfo> Manager::look_for_changed_files(const QString& topdir, const QString& subdir){
    //TODO: Handle removing files
    //TODO: Handle renaming files
    QDir dir(QString(topdir).append("/").append(subdir));
    QFileInfoList list = dir.entryInfoList();

    QList<QFileInfo> result;
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo info = list.at(i);
        QString subpath = QString(subdir).append("/").append(info.fileName());
        if(info.isDir() && !info.isSymLink()){//TODO: Implement following symlinks?
            result += look_for_changed_files(topdir, subpath);
        }else{
            //See if the file has changed
            QSqlQuery query;
            query.prepare("SELECT last_modification, sha1_sum FROM watched_files path=:subpath");
            query.bindValue("subpath", subpath);
            query.exec();
            if(query.size()>0){
                query.next();
                if(info.lastModified() != query.value(0).toDateTime()){
                    QByteArray hash = make_sha1_sum(info.absoluteFilePath());
                    if(hash.length()==0 || QString(hash) != query.value(1)){
                        result.append(info); //File changed
                    }
                }
            }else{//New file
                result.append(info);
            }
        }
    }
    return result;
}

void Manager::notifyDirectoryChanged(const QString& path){
    //Walk trough directory and look for changed files
    //TODO: Check if it is faster to load all files into an hashtable
    //TODO: Check if the reported path is correct (i.e. what we where watching)
    QList<QFileInfo> changed_files = look_for_changed_files(path);
    filesChanged(changed_files);
}
void Manager::filesChanged(QList<QFileInfo> files){
    //Handle changed files, talk with the protocol etc.
}
}
