#include "MAVLinkProtocol.h"
#include <QDebug>

//NetworkUDP* MAVLinkProtocol::_udplink = new NetworkUDP;

MAVLinkProtocol::MAVLinkProtocol()
{
    _seriallink = new SerialLink;
    _udplink    = new NetworkUDP;
    QObject::connect(_seriallink, &SerialLink::bytesReceived, this, &MAVLinkProtocol::receiveByte);
    QObject::connect(_udplink, &NetworkUDP::bytesReceived, this, &MAVLinkProtocol::receiveByte);
}

void MAVLinkProtocol::receiveByte(QByteArray b)
{
    for (int position = 0; position < b.size(); position++){
        //qDebug()<<mavlink_parse_char(1, static_cast<uint8_t>(b[position]), &_message, &_status);
        if (mavlink_parse_char(1, static_cast<uint8_t>(b[position]), &_message, &_status)){
            emit messageReceived(_message);
        }
    }
}

