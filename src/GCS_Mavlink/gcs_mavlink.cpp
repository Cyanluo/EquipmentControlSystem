#include "gcs_mavlink.h"
#include <QDebug>

GCS_Mavlink::GCS_Mavlink()
{
    connect(_mavprotocol,&MAVLinkProtocol::messageReceived,this,&GCS_Mavlink::handle_inter);


}

void GCS_Mavlink::handle_inter(mavlink_message_t msg)
{
    emit received(msg);
}
























//void GCS_Mavlink::sendData(const mavlink_message_t *msg)
//{
//    uint8_t sendbuf[MAVLINK_MAX_PACKET_LEN];
//    mavlink_msg_to_send_buffer(sendbuf,msg);
//    qDebug()<<sendbuf[0]<<sendbuf[1]<<sendbuf[2]<<sendbuf[3]<<sendbuf[4]<<sendbuf[5]<<sendbuf[6]<<sendbuf[7]<<sendbuf[8]<<sendbuf[9]<<sendbuf[10]<<sendbuf[11]<<sendbuf[12]<<sendbuf[13];
//    serial->write((const char*)sendbuf);
//}



