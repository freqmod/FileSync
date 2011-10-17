#include "connection.h"
#include "filesync.pb.h"
#include "prototools.h"
namespace FileShare {
Connection::Connection(QObject *parent) :
    QObject(parent)
{
    current_packet_len = 0;
    remaining_extra_data_length = 0;
    currentPacket = NULL;
}
Connection::~Connection(){
    if(currentPacket)
        delete currentPacket;
}

#define min(a,b)    ((a)<(b)?(a):(b))
void Connection::readyRead(){
    if(remaining_extra_data_length!=0){
        uint32_t toread = min(remaining_extra_data_length, EXTRA_DATA_BLOCK_SIZE);
        QByteArray extra_data = socket.read(toread);
        remaining_extra_data_length-=extra_data.size();
        gotExtraData(currentPacket, extra_data);
    } else{
        if(currentBuffer.length()==0){
            //New buffer
            QByteArray length = socket.read(2);
            current_packet_len = length.at(0) << 8 & length.at(1);
            currentBuffer = socket.read(current_packet_len);
        }else if(currentBuffer.length()>0){
            currentBuffer.append(socket.read(current_packet_len-currentBuffer.length()));
        }
        if(currentBuffer.length() == current_packet_len){
            current_packet_len = 0;
            if(currentPacket){
                delete currentPacket;
                currentPacket = NULL;
            }
            Packet *pkg = new Packet();
            pkg->ParseFromArray(currentBuffer.constData(),currentBuffer.size());
            if(pkg->has_extra_data_length()){
                remaining_extra_data_length = pkg->extra_data_length();
            }
            currentPacket = pkg;
            gotPacket(pkg);
            currentBuffer.clear();
        }
    }
}
void Connection::sendPacket(Packet *pkg){
    uint16_t written_now = 0;
    QByteArray header;
    QByteArray data = serializeToByteArray(pkg);
    header.append((uint8_t)((data.size()&0xFF00)>>8));
    header.append((uint8_t)((data.size()&0x00FF)));
    header.append(data);
    uint16_t data_left = header.size();
    while(data_left > 0){
        written_now = socket.write(header.right(data_left));
        if(written_now < 1){
            break;
        }
        data_left -= written_now;
    }
}

void Connection::gotPacket(Packet *pkg){

}
void Connection::gotExtraData(Packet *pkg, QByteArray data){
}
}
