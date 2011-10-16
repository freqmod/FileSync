#include "connection.h"
#include "filesync.pb.h"
namespace FileShare {
Connection::Connection(QObject *parent) :
    QObject(parent)
{
    current_packet_len = 0;
    remaining_extra_data_length = 0;
}
#define min(a,b)    ((a)<(b)?(a):(b))
void Connection::readyRead(){
    if(remaining_extra_data_length!=0){
        uint32_t toread = min(remaining_extra_data_length, EXTRA_DATA_BLOCK_SIZE);
        QByteArray extra_data = socket.read(toread);
        remaining_extra_data_length-=extra_data.size();
        gotExtraData(extra_data);
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
            Packet pkg;
            pkg.ParseFromArray(currentBuffer.constData(),currentBuffer.size());
            if(pkg.has_extra_data_length()){
                remaining_extra_data_length = pkg.extra_data_length();
            }
            gotPacket(&pkg);
            currentBuffer.clear();
        }
    }
}
void Connection::gotPacket(Packet *pkg){

}
void Connection::gotExtraData(QByteArray data){
}
}
