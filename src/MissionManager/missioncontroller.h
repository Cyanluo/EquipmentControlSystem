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
    Q_INVOKABLE void            sendToVehicle(void);
    Q_INVOKABLE void            loadFromVehicle();                //读取飞控航点数据
    //将polygons的航点数据传给misssioncontroller，类似于拷贝一份
    static QmlObjectListModel*  missionlist;

    QList<MavMission*>*         getMavMission(void)          {return &_missionItems;}
    //static GCS_Mavlink *my_mavlink;

private:
    int                         _lastMissionRequestSeq;         //记录最新的任务请求序号
    QTimer*                     _ackTimeoutTimer = nullptr;


private:
    void sendItemsToVehicle(QmlObjectListModel* MissionItemsList);
    void writeMissionItem();
    void writeMissionCount();
    void connectToMavlink();               //连接mavlink
    void disConnectFromMavlink();          //断开mavlink连接
    void initMavmission(QmlObjectListModel* MissionItems);       //将missionitem转换为mavlink需要的mavmissionitem
    void _handleMissionRequest(mavlink_message_t message, bool missionItemInt);
    void _handleMissionCount(mavlink_message_t message);
    void _requestNextMissionItem(void);
    void _handleMissionItem(const mavlink_message_t& message, bool missionItemInt);
    void _handleMissionAck(const mavlink_message_t &message);       //处理飞控发送的应答信号
    void _finishedTransmit(bool succeed);          //判断是否成功完成任务发送
    void _startMissionTimeout(AckType_t ack);      //判断哪一类定时，设置相应定时时间
    void _requestList(void);                      //发送数据请求
    void _readTransactionComplete();


    MAV_MISSION_TYPE    mission_type = MAV_MISSION_TYPE_ROBOTARMWP;

    Vehicle*            _vehicle = nullptr;
    QList<MavMission*>  _writeMissionItems;     //存储要发给飞控的任务点数据
    QList<MavMission*>  _missionItems;          //存储从飞控读取的任务点数据

    AckType_t           _expectedAck = AckNone;          //当前是响应哪一类信号，即地面站期望的响应类型

protected:
    QList<int>          _itemIndicesToRead;
    int                 _missionItemCountToRead;  // Count of all mission items to read
    void                _clearAndDeleteMissionItems(void);

signals:
    void                readComplete();

private slots:
    void                _mavlinkMessageReceived(const mavlink_message_t &msg);
    void                _ackTimeout(void);
};


#endif // MISSIONCONTROLLER_H
