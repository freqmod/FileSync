#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include <QSslSocket>
#include "clientconnection.h"
namespace FileShare {
class Packet;
class ClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(QObject *parent = 0);

protected:
    QByteArray currentBuffer;
    QSslSocket socket;
signals:

public slots:
    virtual void gotPacket(Packet *pkg);
    virtual void gotExtraData(QByteArray data);
};
}

#endif // CLIENTCONNECTION_H
