#include "vehicle.h"
#include <QDebug>

//GCS_Mavlink* Vehicle::my_mavlink = new GCS_Mavlink;

Vehicle::Vehicle()
{
    connect(HBTimer, &QTimer::timeout, this, &Vehicle::oneSecondLoop);
    HBTimer->start(1000);
    connect(timer,&QTimer::timeout,this,&Vehicle::arduDisconnect);
    connect(my_mavlink,&GCS_Mavlink::received,this,&Vehicle::_mavlinkMessageReceived);
}





void Vehicle::_mavlinkMessageReceived(mavlink_message_t msg)
{
    //传给missioncontroller
    emit receiveMissionMsg(msg);
    //qDebug()<<msg.msgid;
    switch (msg.msgid) {
    case MAVLINK_MSG_ID_HEARTBEAT:
        handleHeartBeatMessage(msg);
        break;
    case MAVLINK_MSG_ID_TEST:
        handleTestMessgae(msg);
        break;
    case MAVLINK_MSG_ID_ATTITUDE:
        handleAttitude(msg);
        break;
    case MAVLINK_MSG_ID_ALTITUDE:
        handleAltitude(msg);
        break;
    case MAVLINK_MSG_ID_POWER_STATUS:
        handlePowerStatus(msg);
        break;
    default:
        //qDebug()<<"没有处理的消息id："<<msg.msgid;
        break;
    }
}



void Vehicle::handleTestMessgae(mavlink_message_t msg)
{
    mavlink_test_t test;
    mavlink_msg_test_decode(&msg,&test);
    //qDebug()<<test.byte1<<test.byte2<<test.byte3<<test.byte4<<test.byte5<<test.byte6;
}

void Vehicle::handleAltitude(mavlink_message_t msg)
{
    mavlink_altitude_t altitude;
    mavlink_msg_altitude_decode(&msg,&altitude);
    qDebug()<<altitude.altitude_relative;
}

void Vehicle::handleAttitude(mavlink_message_t msg)
{
    mavlink_attitude_t attitude;
    mavlink_msg_attitude_decode(&msg,&attitude);
    setPitch(attitude.pitch);
    setYaw(attitude.yaw);
    setRoll(attitude.roll);
    //qDebug()<<attitude.pitch<<"//"<<attitude.yaw<<"//"<<attitude.roll;
    if(initYawOffset || reconnect){
        setYawOffset(attitude.yaw);
        initYawOffset = false;
        reconnect = false;
    }

}

void Vehicle::handlePowerStatus(mavlink_message_t msg)
{
    mavlink_power_status_t powerStatus;
    mavlink_msg_power_status_decode(&msg,&powerStatus);
    setPowerVcc(powerStatus.Vcc);
    //qDebug()<<powerStatus.Vcc<<"//"<<powerStatus.Vservo<<"//"<<powerStatus.flags;
}



void Vehicle::handleHeartBeatMessage(mavlink_message_t msg)
{
    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&msg,&heartbeat);
//    qDebug()<<"recevied heartbeat message";
//    qDebug()<<heartbeat.mavlink_version;
//    qDebug()<<heartbeat.autopilot;
//    qDebug()<<heartbeat.base_mode;
//    qDebug()<<heartbeat.custom_mode;
//    qDebug()<<heartbeat.system_status;
//    qDebug()<<heartbeat.type;

    sendHeartBeatToVehicle(heartbeat.custom_mode,
                           heartbeat.mavlink_version,
                           heartbeat.autopilot,
                           heartbeat.base_mode,
                           heartbeat.system_status,
                           heartbeat.type);

    checkConnect();              //启动两秒定时器，监测心跳包，类似于看门狗
    if(heartbeatCount<4){
        if(heartbeatCount == 0){
            setBeginConnect(true);
        }
        heartbeatCount++;
    }
    else{
        setIsConnected(true);
        //setBeginConnect(false);
    }
}

void Vehicle::sendHeartBeatToVehicle(uint32_t custom_mode,uint8_t mavlink_version,
                                     uint8_t autopilot,uint8_t base_mode,
                                     uint8_t system_status,uint8_t type)
{
    mavlink_heartbeat_t heartBeat;
    heartBeat.mavlink_version = mavlink_version;
    heartBeat.autopilot = autopilot;
    heartBeat.base_mode = base_mode;
    heartBeat.custom_mode = custom_mode;
    heartBeat.system_status = system_status;
    heartBeat.type = type;

    mavlink_message_t message;
    mavlink_msg_heartbeat_encode(1,
                                 1,
                                 &message,
                                 &heartBeat);

    uint8_t buff[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buff,&message);
    my_mavlink->_mavprotocol->_seriallink->sendMavlinkMessage((const char*)buff, len);
    my_mavlink->_mavprotocol->_udplink->sendMavlinkMessage((const char*)buff, len);
}

void Vehicle::checkConnect()
{
    timer->start(2000);
}

void Vehicle::arduDisconnect()
{
    timer->stop();
    setBeginConnect(false);
    setIsConnected(false);
    reconnect = true;
    heartbeatCount = 0;

    //重置roll，yaw，picth
    setRoll(0);
    setPitch(0);
    setYaw(yawOffset);
    //qDebug()<<"disconnect";
}

float Vehicle::getPitch()
{
    return pitch;
}

void Vehicle::setPitch(float x)
{
    pitch = x;
    emit pitchChanged();
}

float Vehicle::getYaw()
{
    return yaw;
}


void Vehicle::setYaw(float x)
{
    yaw = x;
    emit yawChanged();
}

float Vehicle::getRoll()
{
    return roll;
}

void Vehicle::setRoll(float x)
{
    roll = x;
    emit rollChanged();
}

void Vehicle::setYawOffset(float x)
{
    yawOffset = x;
    emit yawOffsetChanged();
}

void Vehicle::setBeginConnect(bool x)
{
    beginConnect = x;
    emit beginConnectChanged();
}

void Vehicle::setIsConnected(bool x)
{
    isConnected = x;
    emit isConnectedChanged();
}

void Vehicle::setPowerVcc(int pv)
{
    powerVcc = pv;
    emit powerVccChanged();
}

void Vehicle::oneSecondLoop()
{
    //qDebug()<<"send one second loop";
    sendHeartBeatToVehicle(4,3,3,1,5,10);
}


