#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>
#include <QSslSocket>
#include "connection.h"
namespace FileShare {
class Packet;
class ServerConnection : public Connection
{
    Q_OBJECT
public:
    explicit ServerConnection(QObject *parent = 0);

protected:
    QByteArray currentBuffer;
    QSslSocket socket;

    void handleConnect(Packet *pkg);
signals:

public slots:
    virtual void gotPacket(Packet *pkg);
    virtual void gotExtraData(Packet *pkg, QByteArray data);
};
}

#endif // SERVERCONNECTION_H
