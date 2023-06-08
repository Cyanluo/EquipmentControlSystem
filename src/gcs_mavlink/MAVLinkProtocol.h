#ifndef MAVLINKPROTOCOL_H
#define MAVLINKPROTOCOL_H

#include <QObject>
#include <src/gcs_mavlink/seriallink.h>
#include <src/gcs_mavlink/seriallink.h>
#include <ardupilotmega/mavlink.h>
#include "src/gcs_mavlink/NetworkUDP.h"

class MAVLinkProtocol:public QObject
{
    Q_OBJECT
public:
    MAVLinkProtocol();

signals:
    void messageReceived(mavlink_message_t message);
public slots:
    void receiveByte(QByteArray b);
public:
    SerialLink* _seriallink = nullptr;
    static NetworkUDP* _udplink;

protected:
    mavlink_message_t _message;
    mavlink_status_t _status;



};

#endif // MAVLINKPROTOCOL_H
