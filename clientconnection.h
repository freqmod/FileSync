#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
namespace FileShare {
class ClientConnection : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnection(QObject *parent = 0);

signals:

public slots:

};
}

#endif // CLIENTCONNECTION_H
