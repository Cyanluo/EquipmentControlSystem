#ifndef GCS_MAVLINK_H
#define GCS_MAVLINK_H

#include <QObject>
#include <ardupilotmega/mavlink.h>
//#include <QtSerialPort/QSerialPort>
//#include <QtSerialPort/QSerialPortInfo>
#include <src/gcs_mavlink/MAVLinkProtocol.h>

class GCS_Mavlink :public QObject
{
    Q_OBJECT
public:
    GCS_Mavlink();

    //void sendData(const mavlink_message_t *msg);



signals:
    void received(mavlink_message_t msg);
    void send();

public slots:
    void handle_inter(mavlink_message_t msg);

    //void readData();

public:
    MAVLinkProtocol* _mavprotocol = new MAVLinkProtocol;;



};

#endif // GCS_MAVLINK_H
