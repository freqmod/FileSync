#include "clientconnection.h"
namespace FileShare {
ClientConnection::ClientConnection(QObject *parent) :
    QObject(parent)
{
}
void ClientConnection::gotPacket(Packet *pkg){

}
void ClientConnection::gotExtraData(Packet *pkg, QByteArray data){
}

}
