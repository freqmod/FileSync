#ifndef CONNECTION_H
#define CONNECTION_H
#define EXTRA_DATA_BLOCK_SIZE 1024*1024

#include <QObject>
#include <QSslSocket>
namespace FileShare {
class Packet;
class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = 0);
    ~Connection();
protected:
    QByteArray currentBuffer;
    QSslSocket socket;
    uint16_t current_packet_len;
    uint64_t remaining_extra_data_length;
    Packet *currentPacket;

    void sendPacket(Packet *pkg);//caller has to send extra data if applicable
signals:

public slots:
    void readyRead();
    virtual void gotPacket(Packet *pkg);
    virtual void gotExtraData(Packet *pkg, QByteArray data);


};
}

#endif // SERVERCONNECTION_H
