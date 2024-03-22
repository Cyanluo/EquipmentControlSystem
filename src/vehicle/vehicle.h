#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include "src/gcs_mavlink/gcs_mavlink.h"
#include "src/vehicle/TBM_Trace.h"
#include <QFile>
#include <QDataStream>
#include <QTimer>
#include "src/ECSToolbox.h"
#include "src/vehicle/InitialConnectStateMachine.h"

class ParameterManager;

enum ap_var_type {
    AP_PARAM_NONE    = 0,
    AP_PARAM_INT8,
    AP_PARAM_INT16,
    AP_PARAM_INT32,
    AP_PARAM_FLOAT,
    AP_PARAM_VECTOR3F,
    AP_PARAM_GROUP
};

enum Mode : uint8_t {
    MANUAL       = 0,
    ACRO         = 1,
    STEERING     = 3,
    HOLD         = 4,
    LOITER       = 5,
    FOLLOW       = 6,
    SIMPLE       = 7,
    AUTO         = 10,
    RTL          = 11,
    SMART_RTL    = 12,
    GUIDED       = 15,
    INITIALISING = 16,
    TBM          = 17,
    EXCAVATOR    = 18
};

class Vehicle :public QObject
{
    Q_OBJECT

public slots:
    void _mavlinkMessageReceived(mavlink_message_t msg);
    void arduDisconnect(void);
    void parameterReady(bool ready);
    void setProgress(int componentId, float value);

public:
    Vehicle();
    ~Vehicle();

    Q_PROPERTY(float pitch        READ getPitch        WRITE setPitch        NOTIFY pitchChanged)
    Q_PROPERTY(float yaw          READ getYaw          WRITE setYaw          NOTIFY yawChanged)
    Q_PROPERTY(float roll         READ getRoll         WRITE setRoll         NOTIFY rollChanged)
    Q_PROPERTY(float yawOffset    READ getYawOffset    WRITE setYawOffset    NOTIFY yawOffsetChanged)
    Q_PROPERTY(bool  beginConnect READ getBeginConnect WRITE setBeginConnect NOTIFY beginConnectChanged)
    Q_PROPERTY(bool  isConnected  READ getIsConnected  WRITE setIsConnected  NOTIFY isConnectedChanged)
    Q_PROPERTY(int   powerVcc     READ getPowerVcc     WRITE setPowerVcc     NOTIFY powerVccChanged)
    Q_PROPERTY(int   planScreenW  READ getPlanScreenW  WRITE setPlanScreenW  NOTIFY PlanScreenWChanged)
    Q_PROPERTY(int   planScreenH  READ getPlanScreenH  WRITE setPlanScreenH  NOTIFY PlanScreenHChanged)

    Q_PROPERTY(float    progress   READ    progress      CONSTANT)

signals:
    void pitchChanged();
    void yawChanged();
    void rollChanged();
    void yawOffsetChanged();
    void beginConnectChanged();
    void isConnectedChanged();
    void powerVccChanged();
    void receiveMissionMsg(const mavlink_message_t& message);
    void PlanScreenWChanged();
    void PlanScreenHChanged();
    void receiveMavMsg(QString msg);

public:
    Q_INVOKABLE void saveMavToFile(bool flag);
    Q_INVOKABLE void getPlanScreenWH(int W, int H);
    Q_INVOKABLE void setVehicleEncipher(bool enable);
    Q_INVOKABLE void setMode(unsigned int new_mode);

    MAV_TYPE    type()          const { return _type;           }
    uint8_t     sysid()         const { return _sysid;          }
    uint8_t     compid()        const { return _compid;         }
    uint8_t     defaultCompid() const { return _defaultCompid;  }

    GCS_Mavlink     *my_mavlink     =   nullptr;
    TBM_Trace       *_tbmTrace      =   new TBM_Trace;
    static int      planScreenW;                        //记录当前的plan屏幕的宽度
    static int      planScreenH;                        //记录当前的plan屏幕的高度

private:
    void   handleHeartBeatMessage(mavlink_message_t& msg);
    void   handleAltitude(mavlink_message_t& msg);
    void   handleAttitude(mavlink_message_t& msg);
    void   handlePowerStatus(mavlink_message_t& msg);
    void   handleTBM_Positional_Parameters(mavlink_message_t& msg);
    void   handleMsgIdStatustext(mavlink_message_t& msg);
    void   handleMsgIdCommandAck(mavlink_message_t& msg);
    void   sendHeartBeatToVehicle(uint32_t custom_mode,uint8_t mavlink_version,uint8_t autopilot,uint8_t base_mode,uint8_t system_status,uint8_t type);
    void   checkConnect();

    float   getPitch()                       { return pitch;          }
    float   getRoll()                        { return roll;           }
    float   getYaw()                         { return yaw;            }
    float   getYawOffset()                   { return yawOffset;      }
    int     getPowerVcc()                    { return powerVcc;       }
    int     getPlanScreenH(void)             { return planScreenH;    }
    int     getPlanScreenW(void)             { return planScreenW;    }
    bool    getIsConnected()                 { return isConnected;    }
    bool    getBeginConnect()                { return beginConnect;   }
    float   progress()                       { return _progress;      }

    void    setPitch(float x);
    void    setYaw(float x);
    void    setRoll(float x);
    void    setYawOffset(float x);
    void    setPowerVcc(int pv);
    void    setPlanScreenW(int W);
    void    setPlanScreenH(int H);
    void    setBeginConnect(bool x);
    void    setIsConnected(bool x);

    void changeSaveMavMsgFlag();
    void truncate_buff(uint8_t* buff, int len);

    QString severity2String(MAV_SEVERITY severity);

    float   pitch             = 0;
    float   yaw               = 0;
    float   roll              = 0;
    int     powerVcc          = 0;
    float   yawOffset         = 0;          //保存第一次偏航数据，所谓偏置角
    int     heartbeatCount    = 0;
    bool    initYawOffset     = true;       //在第一次收到yaw值时赋值
    bool    reconnect         = false;      //在重新连接时更新yaw offset
    bool    beginConnect      = false;
    bool    isConnected       = false;
    float   _progress         = 0;

    QFile           writeFile;
    QDataStream     out;
    bool            mavFlag = false;
    uint8_t         buff[MAVLINK_MAX_PACKET_LEN] = {0};

    MAV_TYPE        _type;
    uint8_t         _sysid  = 1;
    uint8_t         _compid = 1;
    uint32_t        _custom_mode;
    uint8_t         _base_mode;
    uint8_t         _defaultCompid = 1;

    QTimer *timer         = new QTimer(this);
    QTimer *WDTimer       = new QTimer(this);

    ECSToolbox*                 _toolbox            = nullptr;
    InitialConnectStateMachine* _initStateMachine   = nullptr;
    ParameterManager*           _parameterManager   = nullptr;
};

#endif // VEHICLE_H
