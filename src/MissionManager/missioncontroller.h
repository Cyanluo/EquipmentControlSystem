#ifndef MISSIONCONTROLLER_H
#define MISSIONCONTROLLER_H

#include <QObject>
#include <QWidget>
#include "qmlobjectlistmodel.h"
#include "ardupilotmega/mavlink.h"
#include "src/vehicle/vehicle.h"
#include "src/MissionManager/mavmission.h"
#include "src/MissionManager/missionitem.h"
#include "QTimer"




class MissionController :public QObject
{
    Q_OBJECT
public:
    MissionController(Vehicle *vehicle);

    typedef enum {
        AckNone,            ///< State machine is idle
//        AckMissionCount,    ///< MISSION_COUNT message expected
//        AckMissionItem,     ///< MISSION_ITEM expected
        AckMissionRequest,  ///< MISSION_REQUEST is expected, or MISSION_ACK to end sequence
        AckMissionClearAll, ///< MISSION_CLEAR_ALL sent, MISSION_ACK is expected
//        AckGuidedItem,      ///< MISSION_ACK expected in response to ArduPilot guided mode single item send
    } AckType_t;

    //界面的上传航点按钮对应
    Q_INVOKABLE void sendToVehicle(void);
    //将polygons的航点数据传给misssioncontroller，类似于拷贝一份
    static QmlObjectListModel* missionlist;
    //static GCS_Mavlink *my_mavlink;

private:
    int _lastMissionRequestSeq;         //记录最新的任务请求序号
    QTimer*     _ackTimeoutTimer = nullptr;

private:
    void sendItemsToVehicle(QmlObjectListModel* MissionItemsList);
    void writeMissionItem();
    void writeMissionCount();
    void connectToMavlink();               //连接mavlink
    void disConnectFromMavlink();          //断开mavlink连接
    void initMavmission(QmlObjectListModel* MissionItems);       //将missionitem转换为mavlink需要的mavmissionitem
    void _handleMissionRequest(mavlink_message_t message, bool missionItemInt);
    void _handleMissionAck(const mavlink_message_t &message);       //处理飞控发送的应答信号
    void _finishedTransmit(bool succeed);          //判断是否成功完成任务发送
    void _startMissionTimeout(AckType_t ack);      //判断哪一类定时，设置相应定时时间


    MAV_MISSION_TYPE mission_type = MAV_MISSION_TYPE_MISSION;

    Vehicle* _vehicle = nullptr;
    QList<MavMission*> _writeMissionItems;

    AckType_t _expectedAck = AckNone;          //当前是响应哪一类信号，即地面站期望的响应类型

private slots:
    void _mavlinkMessageReceived(const mavlink_message_t &msg);
    void _ackTimeout(void);
};


#endif // MISSIONCONTROLLER_H
