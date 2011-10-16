#include "clientconnection.h"
namespace FileShare {
ClientConnection::ClientConnection(QObject *parent) :
    QObject(parent)
{
}
void ClientConnection::gotPacket(Packet *pkg){

}
void ClientConnection::gotExtraData(QByteArray data){
}

}
