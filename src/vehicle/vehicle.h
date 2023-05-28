#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include "src/gcs_mavlink/gcs_mavlink.h"

class Vehicle :public QObject
{
    Q_OBJECT



public slots:
    void _mavlinkMessageReceived(mavlink_message_t msg);
    void arduDisconnect(void);



public:
    Vehicle();

    Q_PROPERTY(float pitch        READ getPitch        WRITE setPitch        NOTIFY pitchChanged)
    Q_PROPERTY(float yaw          READ getYaw          WRITE setYaw          NOTIFY yawChanged)
    Q_PROPERTY(float roll         READ getRoll         WRITE setRoll         NOTIFY rollChanged)
    Q_PROPERTY(float yawOffset    READ getYawOffset    WRITE setYawOffset    NOTIFY yawOffsetChanged)
    Q_PROPERTY(bool  beginConnect READ getBeginConnect WRITE setBeginConnect NOTIFY beginConnectChanged)
    Q_PROPERTY(bool  isConnected  READ getIsConnected  WRITE setIsConnected  NOTIFY isConnectedChanged)
    Q_PROPERTY(int   powerVcc     READ getPowerVcc     WRITE setPowerVcc     NOTIFY powerVccChanged)


signals:
    void pitchChanged();
    void yawChanged();
    void rollChanged();
    void yawOffsetChanged();
    void beginConnectChanged();
    void isConnectedChanged();
    void powerVccChanged();
    void receiveMissionMsg(const mavlink_message_t& message);


public:
    QTimer *timer         = new QTimer(this);

    float pitch          = 0;
    float yaw            = 0;
    float roll           = 0;
    int   powerVcc       = 0;
    float yawOffset      = 0;          //保存第一次偏航数据，所谓偏置角
    int   heartbeatCount = 0;

    bool  initYawOffset  = true;       //在第一次收到yaw值时赋值
    bool  reconnect      = false;      //在重新连接时更新yaw offset
    bool  beginConnect   = false;
    bool  isConnected    = false;

    GCS_Mavlink* my_mavlink = new GCS_Mavlink;;



private:
    void   handleHeartBeatMessage(mavlink_message_t msg);
    void   handleTestMessgae(mavlink_message_t msg);
    void   handleAltitude(mavlink_message_t msg);
    void   handleAttitude(mavlink_message_t msg);
    void   handlePowerStatus(mavlink_message_t msg);
    void   sendHeartBeatToVehicle(uint32_t custom_mode,uint8_t mavlink_version,uint8_t autopilot,uint8_t base_mode,uint8_t system_status,uint8_t type);
    void   checkConnect();
    float  getPitch();
    float  getRoll();
    float  getYaw();
    float  getYawOffset()                            {return yawOffset;   }
    bool   getBeginConnect()                         {return beginConnect;}
    bool   getIsConnected()                          {return isConnected; }
    int    getPowerVcc()                             {return powerVcc;    }
    void   setPitch(float x);
    void   setYaw(float x);
    void   setRoll(float x);
    void   setYawOffset(float x);
    void   setBeginConnect(bool x);
    void   setIsConnected(bool x);
    void   setPowerVcc(int pv);





};


#endif // VEHICLE_H
