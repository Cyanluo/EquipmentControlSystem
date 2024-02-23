#include "vehicle.h"
#include <QDebug>
#include <QDir>
#include <QDateTime>
#include "src/ECSApplication.h"

int Vehicle::planScreenW = 0;
int Vehicle::planScreenH = 0;

Vehicle::Vehicle()
    :_toolbox(ecsApp()->toolbox())
{
    QDateTime dateTime= QDateTime::currentDateTime();
    QString str = dateTime .toString("yyyy-MM-dd hh-mm-ss");
    writeFile.setFileName(str + ".dat");
    QDir::setCurrent("./data");
    out.setDevice(&writeFile);

    my_mavlink = _toolbox->linkManager();

    connect(my_mavlink, &GCS_Mavlink::received, this, &Vehicle::_mavlinkMessageReceived);
    connect(HBTimer, &QTimer::timeout, this, &Vehicle::oneSecondLoop);
    // HBTimer->start(1000);
    connect(timer, &QTimer::timeout, this, &Vehicle::arduDisconnect);
    connect(WDTimer, &QTimer::timeout, this, &Vehicle::changeSaveMavMsgFlag);
}

void Vehicle::_mavlinkMessageReceived(mavlink_message_t msg)
{
    //传给missioncontroller
    emit receiveMissionMsg(msg);

    switch (msg.msgid) {
        case MAVLINK_MSG_ID_TBM_UNITY_INTERFACE:
        {
            if(mavFlag)
            {
                int len = mavlink_msg_to_send_buffer(buff, &msg);
                out << len;
                out.writeRawData((char *)buff, len);
                truncate_buff(buff, MAVLINK_MAX_PACKET_LEN);
            }

            mavlink_tbm_unity_interface_t unity_interface;
            mavlink_msg_tbm_unity_interface_decode(&msg, &unity_interface);

            break;
        }
    }

    switch (msg.msgid) {
    case MAVLINK_MSG_ID_HEARTBEAT:
        handleHeartBeatMessage(msg);
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

    case MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS:
        handleTBM_Positional_Parameters(msg);
        break;

    case MAVLINK_MSG_ID_RANGEFINDER:
        handleRangefinder(msg);
        break;

    case MAVLINK_MSG_ID_STATUSTEXT:
        handleMsgIdStatustext(msg);
        break;

    default:
        //qDebug()<<"没有处理的消息id："<<msg.msgid;
        break;
    }
}

void Vehicle::changeSaveMavMsgFlag()
{
    mavFlag = true;
}

void Vehicle::saveMavToFile(bool flag)
{
    if(flag)
    {
        writeFile.open(QIODevice::WriteOnly | QIODevice::Append);
        mavFlag = true;
    }
    else
    {
        mavFlag = false;
        writeFile.close();
    }
}

void Vehicle::handleAltitude(mavlink_message_t& msg)
{
    mavlink_altitude_t altitude;
    mavlink_msg_altitude_decode(&msg,&altitude);
    qDebug()<<altitude.altitude_relative;
}

void Vehicle::handleAttitude(mavlink_message_t& msg)
{
    mavlink_attitude_t attitude;
    mavlink_msg_attitude_decode(&msg,&attitude);
    setPitch(attitude.pitch);
    setYaw(attitude.yaw);
    setRoll(attitude.roll);
    if(initYawOffset || reconnect){
        setYawOffset(attitude.yaw);
        initYawOffset = false;
        reconnect = false;
    }
}

void Vehicle::handlePowerStatus(mavlink_message_t& msg)
{
    mavlink_power_status_t powerStatus;
    mavlink_msg_power_status_decode(&msg,&powerStatus);
    setPowerVcc(powerStatus.Vcc);
}

void Vehicle::handleTBM_Positional_Parameters(mavlink_message_t& msg)
{
    mavlink_tbm_positional_parameters_t tbm_pp;
    mavlink_msg_tbm_positional_parameters_decode(&msg, &tbm_pp);
    _tbmTrace->setCoordinate_x(tbm_pp.rdheader_xb*planScreenW/2 + planScreenW/2);   //533是坐标系x偏置
    _tbmTrace->setCoordinate_y(planScreenH - tbm_pp.rdheader_yb*planScreenH);   //608是y向偏置
    // qDebug()<<"rdheader_xb:"<<tbm_pp.rdheader_xb;
    // qDebug()<<"rdheader_yb:"<<tbm_pp.rdheader_yb;
}

void Vehicle::handleRangefinder(mavlink_message_t& msg)
{

}

void Vehicle::handleHeartBeatMessage(mavlink_message_t& msg)
{
    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&msg,&heartbeat);

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
    my_mavlink->sendData((const char*)buff, len);
}

void Vehicle::handleMsgIdStatustext(mavlink_message_t& msg)
{
    static QString textStr;
    static uint16_t last_textid = -1;

    mavlink_statustext_t text;
    mavlink_msg_statustext_decode(&msg, &text);

    if(text.id == 0)
    {
        emit receiveMavMsg(severity2String((MAV_SEVERITY)text.severity) + text.text);
    }
    else if(last_textid != text.id && text.chunk_seq == 0)
    {
        if(textStr != "")
        {
            emit receiveMavMsg(severity2String((MAV_SEVERITY)text.severity) + textStr);
        }

        textStr = "";
        text.text[sizeof(text.text)] = 0;
        textStr += text.text;
    }
    else
    {
        textStr += QString(text.text);
    }

    last_textid = text.id;
}

QString Vehicle::severity2String(MAV_SEVERITY severity)
{
    QString ret = "";

    switch (severity) {
    case MAV_SEVERITY_INFO:
        ret = "INFO:";
        break;
    case MAV_SEVERITY_CRITICAL:
        ret = "CRITICAL:";
        break;
    case MAV_SEVERITY_ERROR:
        ret = "ERROR:";
        break;
    case MAV_SEVERITY_DEBUG:
        ret = "DEBUG:";
        break;
    case MAV_SEVERITY_WARNING:
        ret = "WARNING:";
        break;
    case MAV_SEVERITY_NOTICE:
        ret = "NOTICE:";
        break;
    case MAV_SEVERITY_ALERT:
        ret = "ALERT:";
        break;
    case MAV_SEVERITY_EMERGENCY:
        ret = "EMERGENCY:";
        break;
    default:
        ret = "";
        break;
    }

    return ret;
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

void Vehicle::setPlanScreenW(int W)
{
    planScreenW = W;
    emit PlanScreenWChanged();
}

void Vehicle::setPlanScreenH(int H)
{
    planScreenH = H;
    emit PlanScreenHChanged();
}

void Vehicle::getPlanScreenWH(int W, int H)
{
    setPlanScreenH(H);
    setPlanScreenW(W);
}

void Vehicle::oneSecondLoop()
{
    sendHeartBeatToVehicle(4,3,3,1,5,10);
}

void Vehicle::truncate_buff(uint8_t* buff, int len)
{
    for(int i=0; i<len; i++)
    {
        buff[i] = 0;
    }
}

void Vehicle::set_param(const char* id, uint8_t param_type, float param_value)
{
    mavlink_param_set_t param_set;
    memset(param_set.param_id, 0, sizeof(param_set.param_id));
    memcpy(param_set.param_id, id, strlen(id));
    param_set.param_type = param_type;
    param_set.param_value = param_value;
    param_set.target_system = 1;
    param_set.target_component = 1;

    mavlink_message_t message;
    mavlink_msg_param_set_encode(1,
                                 1,
                                 &message,
                                 &param_set);

    uint8_t buff[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buff,&message);
    my_mavlink->sendData((const char*)buff, len);
}

void Vehicle::setVehicleEncipher(bool enable)
{
    set_param("ENcipher_enAES", AP_PARAM_INT8, enable ? 1 : 0);
}
