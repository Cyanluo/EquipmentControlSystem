#include "vehicle.h"
#include <QDebug>
#include <QDir>
#include <QDateTime>
#include "src/ECSApplication.h"
#include "src/ParameterManager/ParameterManager.h"

int Vehicle::planScreenW = 0;
int Vehicle::planScreenH = 0;

Vehicle::Vehicle()
    :_toolbox(ecsApp()->toolbox())
    ,_parameterManager(ecsApp()->toolbox()->parameterManager())
{
    QDateTime dateTime= QDateTime::currentDateTime();
    QString str = dateTime .toString("yyyy-MM-dd hh-mm-ss");
    writeFile.setFileName(str + ".dat");
    QDir::setCurrent("./data");
    out.setDevice(&writeFile);

    my_mavlink = _toolbox->linkManager();
    _initStateMachine = new InitialConnectStateMachine(this);

    connect(my_mavlink, &GCS_Mavlink::received, this, &Vehicle::_mavlinkMessageReceived);
    connect(timer, &QTimer::timeout, this, &Vehicle::arduDisconnect);
    connect(WDTimer, &QTimer::timeout, this, &Vehicle::changeSaveMavMsgFlag);
    connect(_parameterManager, &ParameterManager::parametersReadyChanged, this, &Vehicle::parameterReady);
    connect(_parameterManager, &ParameterManager::loadProgressChanged, this, &Vehicle::setProgress);
}

Vehicle::~Vehicle()
{
    delete timer;
    delete WDTimer;
    delete _initStateMachine;
    delete _tbmTrace;
}

void Vehicle::_mavlinkMessageReceived(mavlink_message_t msg)
{
    _parameterManager->mavlinkMessageReceived(msg);

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

    case MAVLINK_MSG_ID_RANGEFINDER:
    // case MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS:
        handleTBM_Positional_Parameters(msg);
        break;

    case MAVLINK_MSG_ID_STATUSTEXT:
        handleMsgIdStatustext(msg);
        break;

    case MAVLINK_MSG_ID_COMMAND_ACK:
        handleMsgIdCommandAck(msg);
        break;

    default:
        break;
    }

    emit receiveMissionMsg(msg);
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

    qDebug() << altitude.altitude_relative;
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
    // mavlink_tbm_positional_parameters_t tbm_pp;
    // mavlink_msg_tbm_positional_parameters_decode(&msg, &tbm_pp);

    mavlink_rangefinder_t tbm_pp;
    mavlink_msg_rangefinder_decode(&msg, &tbm_pp);
    _tbmTrace->setCoordinate_x(tbm_pp.distance*planScreenW/2 + planScreenW/2);
    _tbmTrace->setCoordinate_y(planScreenH - tbm_pp.voltage*planScreenH);

    // _tbmTrace->setCoordinate_x(tbm_pp.rdheader_xb*planScreenW/2 + planScreenW/2);
    // _tbmTrace->setCoordinate_y(planScreenH - tbm_pp.rdheader_yb*planScreenH);
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

    if(msg.compid == _defaultCompid){
        _type = (MAV_TYPE)heartbeat.type;
        _sysid = msg.sysid;
        _compid = msg.compid;
        _custom_mode = heartbeat.custom_mode;
        _base_mode = heartbeat.base_mode;
    }

    if(!_parameterManager->isInitialLoadComplete()) {
        if(heartbeatCount == 0) {
            setBeginConnect(true);
            _initStateMachine->start();
        }
        heartbeatCount++;
    } else {
        if(heartbeatCount <= 3) {
            heartbeatCount++;
        } else if(heartbeatCount > 100) {
            heartbeatCount = 5;
            setIsConnected(true);
        } else {
            setIsConnected(true);
        }
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

void Vehicle::handleMsgIdCommandAck(mavlink_message_t& msg)
{
    mavlink_command_ack_t command_ack;
    mavlink_msg_command_ack_decode(&msg, &command_ack);

    switch (command_ack.command) {
    case MAVLINK_MSG_ID_SET_MODE:
    {
        if(command_ack.result  == MAV_RESULT_FAILED)
        {

        }
        else if(command_ack.result  == MAV_RESULT_ACCEPTED)
        {

        }
        else
        {

        }

        break;
    }
    default:
        break;
    }
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
    reconnect = true;
    heartbeatCount = 0;

    setBeginConnect(false);
    setIsConnected(false);
    setRoll(0);
    setPitch(0);
    setYaw(yawOffset);
}

void Vehicle::parameterReady(bool ready)
{
    if(ready) {
        setIsConnected(true);
        setBeginConnect(false);
    }
}

void Vehicle::setProgress(int componentId, float value)
{
    if(_compid == componentId) {
        _progress = value;
    }
}

void Vehicle::setPitch(float x)
{
    pitch = x;
    emit pitchChanged();
}

void Vehicle::setYaw(float x)
{
    yaw = x;
    emit yawChanged();
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
    if(x == isConnected)
        return;

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

void Vehicle::truncate_buff(uint8_t* buff, int len)
{
    for(int i=0; i<len; i++)
    {
        buff[i] = 0;
    }
}

void Vehicle::setVehicleEncipher(bool enable)
{
    Fact* fact = ecsApp()->toolbox()->parameterManager()->getParameter(_compid, "ENcipher_enAES");

    fact->setRawValue(enable ? 1 : 0);
}

void Vehicle::setMode(unsigned int new_mode)
{
    mavlink_set_mode_t m;
    m.base_mode = _base_mode;
    m.custom_mode = new_mode;
    m.target_system = 1;

    mavlink_message_t message;
    mavlink_msg_set_mode_encode(254,
                                1,
                                &message,
                                &m);

    uint8_t buff[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buff, &message);
    my_mavlink->sendData((const char*)buff, len);
}
