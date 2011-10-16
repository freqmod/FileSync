#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>
#include <QSslSocket>
#include "clientconnection.h"
namespace FileShare {
class ServerConnection : public ClientConnection
{
    Q_OBJECT
public:
    explicit ServerConnection(QObject *parent = 0);

protected:
    QByteArray currentBuffer;
    QSslSocket socket;
signals:

public slots:
    virtual void gotPacket(Packet *pkg);
    virtual void gotExtraData(QByteArray data);
};
}

#endif // SERVERCONNECTION_H
