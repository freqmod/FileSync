#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include <QSslSocket>
namespace FileShare {
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
    void readyRead();
};
}

#endif // CLIENTCONNECTION_H
