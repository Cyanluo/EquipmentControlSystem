#include "missioncontroller.h"
#include <QDebug>

QmlObjectListModel* MissionController::missionlist = nullptr;

MissionController::MissionController(Vehicle* vehicle)
{
    _vehicle = vehicle;

    _ackTimeoutTimer = new QTimer(this);
    connect(_ackTimeoutTimer,&QTimer::timeout,this,&MissionController::_ackTimeout);
}

void MissionController::loadFromVehicle()
{
    //需要判断车辆是否在线，与飞控是否有连接
    connectToMavlink();
    _requestList();
}

void MissionController::_requestList()
{
    _itemIndicesToRead.clear();
    _clearAndDeleteMissionItems();
    mavlink_message_t       message;
    mavlink_msg_mission_request_list_pack_chan(1,//system id
                                               1,//component id
                                               1,//chan
                                               &message,//encode的一帧mavlink消息
                                               1,//目标system id
                                               MAV_COMP_ID_AUTOPILOT1,
                                               mission_type);
    uint8_t buff[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buff, &message);
    _vehicle->my_mavlink->_mavprotocol->_seriallink->sendMavlinkMessage((const char*)buff, len);

}

void MissionController::_readTransactionComplete()
{
    qDebug()<<"_readTransactionComplete";
    mavlink_message_t       message;

    mavlink_msg_mission_ack_pack_chan(1,
                                      1,
                                      1,
                                      &message,
                                      1,
                                      MAV_COMP_ID_AUTOPILOT1,
                                      MAV_MISSION_ACCEPTED,
                                      mission_type);
    uint8_t buff[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buff, &message);
    _vehicle->my_mavlink->_mavprotocol->_seriallink->sendMavlinkMessage((const char*)buff, len);

    disConnectFromMavlink();
    emit readComplete();
}

void MissionController::_clearAndDeleteMissionItems(void)
{
    for (int i=0; i<_missionItems.count(); i++) {
        // Using deleteLater here causes too much transient memory to stack up
        delete _missionItems[i];
    }
    _missionItems.clear();
}

void MissionController::sendToVehicle()
{
    /***
     * 1、判断连接是否正常
     * 2、判断发送的任务列表是否为空
     * 3、调用senditemstovehicle，将_polygons进一步处理、发送
     ***/

    sendItemsToVehicle(missionlist);

}

void MissionController::sendItemsToVehicle(QmlObjectListModel *MissionItemsList)
{
    //可以调到任务列表
    //qDebug()<<"the first x:"<<((missionitem*)MissionItemsList->get(0))->getNumber_x();

    //在此将missionitem转换为mavmissionitem
    initMavmission(MissionItemsList);
    writeMissionItem();

}

void MissionController::writeMissionItem()
{

    connectToMavlink();//连接mavlink，接受飞控请求
    writeMissionCount();//发送总航点数

}

void MissionController::writeMissionCount()
{
    mavlink_message_t message;
    mavlink_msg_mission_count_pack_chan(1,//system id
                                        1,//component id
                                        1,//chan
                                        &message,//encode的一帧mavlink消息
                                        1,//目标system id
                                        1,//目标component id
                                        missionlist->count(),//count
                                        mission_type);//mission type
    uint8_t buff[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buff, &message);
    _vehicle->my_mavlink->_mavprotocol->_seriallink->sendMavlinkMessage((const char*)buff, len);

    _startMissionTimeout(AckMissionRequest);  //开始定时，如果超时未收到MissionRequest应答，做进一步处理

}

void MissionController::connectToMavlink()
{
    connect(_vehicle,&Vehicle::receiveMissionMsg,this,&MissionController::_mavlinkMessageReceived);
}

void MissionController::disConnectFromMavlink()
{
    disconnect(_vehicle,&Vehicle::receiveMissionMsg,this,&MissionController::_mavlinkMessageReceived);
}

void MissionController::initMavmission(QmlObjectListModel *MissionItems)
{

    if (MissionItems->count() == 0) {
        qDebug()<<"initMavmission: mission count = 0";
        return;
    }

    int missionCount;
    missionCount = MissionItems->count();
    for(int seqNum = 0; seqNum < missionCount; seqNum++)
    {
        missionitem* missionItem = qobject_cast<missionitem*>(MissionItems->get(seqNum));
        MavMission* mavMission = new MavMission;
        mavMission->setFrame(MAV_FRAME_GLOBAL);
        mavMission->setAutoContinue(true);
        mavMission->setCommand(MAV_CMD_NAV_WAYPOINT);
        mavMission->setParam1(0);
        mavMission->setParam2(1);
        mavMission->setParam3(1);
        mavMission->setParam4(0);
        mavMission->setParam5(missionItem->getNumber_x());
        mavMission->setParam6(missionItem->getNumber_y());
        mavMission->setParam7(0);
        mavMission->setSequenceNumber(missionItem->getMissionindex());
        _writeMissionItems.append(mavMission);
    }
}

void MissionController::_handleMissionRequest(mavlink_message_t message, bool missionItemInt)
{
    MAV_MISSION_TYPE missionRequestMissionType;
    uint16_t            missionRequestSeq;

    //判断请求任务项类型
    if (missionItemInt) {
        mavlink_mission_request_int_t missionRequest;
        mavlink_msg_mission_request_int_decode(&message, &missionRequest);
        missionRequestMissionType = static_cast<MAV_MISSION_TYPE>(missionRequest.mission_type);
        missionRequestSeq = missionRequest.seq;
    } else {
        mavlink_mission_request_t missionRequest;
        mavlink_msg_mission_request_decode(&message, &missionRequest);
        missionRequestMissionType = static_cast<MAV_MISSION_TYPE>(missionRequest.mission_type);
        missionRequestSeq = missionRequest.seq;
    }

    if(missionRequestMissionType != mission_type)
    {
        qDebug()<< "_handleMissionRequest %1 Incorrect mission_type received expected:actual"<< missionRequestSeq;
        return;
    }

    _lastMissionRequestSeq = missionRequestSeq;

    qDebug()<<"missionRequestSeq:"<<missionRequestSeq;

    MavMission* item = _writeMissionItems[missionRequestSeq];
    mavlink_message_t       messageOut;
    mavlink_msg_mission_item_pack_chan(1,
                                       1,
                                       1,
                                       &messageOut,
                                       1,
                                       MAV_COMP_ID_AUTOPILOT1,
                                       missionRequestSeq,
                                       item->frame(),
                                       item->command(),
                                       missionRequestSeq == 0,
                                       item->autoContinue(),
                                       item->param1(),
                                       item->param2(),
                                       item->param3(),
                                       item->param4(),
                                       item->param5(),
                                       item->param6(),
                                       item->param7(),
                                       mission_type);

    //qDebug()<<"x:"<<item->param5()<<"y:"<<item->param6(); //这里发送的数据是对的
    uint8_t buff[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buff, &messageOut);
    _vehicle->my_mavlink->_mavprotocol->_seriallink->sendMavlinkMessage((const char*)buff, len);

    _startMissionTimeout(AckMissionRequest);
}

void MissionController::_handleMissionCount(mavlink_message_t message)
{
    mavlink_mission_count_t missionCount;

    mavlink_msg_mission_count_decode(&message, &missionCount);

    if (missionCount.mission_type != mission_type) {
        // if there was a previous transaction with a different mission_type, it can happen that we receive
        // a stale message here, for example when the MAV ran into a timeout and sent a message twice
        qDebug() << "_handleMissionCount Incorrect mission_type received expected";
        return;
    }
    // Prime read list
    for (int i=0; i<missionCount.count; i++) {
        _itemIndicesToRead << i;
    }
    _missionItemCountToRead = missionCount.count;
    _requestNextMissionItem();
}

void MissionController::_requestNextMissionItem()
{
    mavlink_message_t       message;
    mavlink_msg_mission_request_int_pack_chan(1,
                                              1,
                                              1,
                                              &message,
                                              1,
                                              MAV_COMP_ID_AUTOPILOT1,
                                              _itemIndicesToRead[0],
                                              mission_type);
    uint8_t buff[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buff, &message);
    _vehicle->my_mavlink->_mavprotocol->_seriallink->sendMavlinkMessage((const char*)buff, len);
}

void MissionController::_handleMissionItem(const mavlink_message_t &message, bool missionItemInt)
{
    MAV_CMD     command;
    MAV_FRAME   frame;
    double      param1;
    double      param2;
    double      param3;
    double      param4;
    double      param5;
    double      param6;
    double      param7;
    bool        autoContinue;
    int         seq;

    if (missionItemInt) {
        mavlink_mission_item_int_t missionItem;
        mavlink_msg_mission_item_int_decode(&message, &missionItem);

        command =       (MAV_CMD)missionItem.command,
        frame =         (MAV_FRAME)missionItem.frame,
        param1 =        missionItem.param1;
        param2 =        missionItem.param2;
        param3 =        missionItem.param3;
        param4 =        missionItem.param4;
        param5 =        missionItem.frame == MAV_FRAME_MISSION ? (double)missionItem.x : (double)missionItem.x;// * 1e-7;
        param6 =        missionItem.frame == MAV_FRAME_MISSION ? (double)missionItem.y : (double)missionItem.y;// * 1e-7;
        //qDebug()<<"in handle missionitem"<<missionItem.x<<"\\"<<missionItem.y;
        param7 =        (double)missionItem.z;
        autoContinue =  missionItem.autocontinue;
        seq =           missionItem.seq;
        qDebug()<<"int";
    } else {
        mavlink_mission_item_t missionItem;
        mavlink_msg_mission_item_decode(&message, &missionItem);

        command =       (MAV_CMD)missionItem.command,
        frame =         (MAV_FRAME)missionItem.frame,
        param1 =        missionItem.param1;
        param2 =        missionItem.param2;
        param3 =        missionItem.param3;
        param4 =        missionItem.param4;
        param5 =        missionItem.x;
        param6 =        missionItem.y;
        param7 =        missionItem.z;
        autoContinue =  missionItem.autocontinue;
        seq =           missionItem.seq;
    }

    if (_itemIndicesToRead.contains(seq)) {
        _itemIndicesToRead.removeOne(seq);
        MavMission* item = new MavMission;
        item->setParam1(param1);
        item->setParam2(param2);
        item->setParam3(param3);
        item->setParam4(param4);
        item->setParam5(param5);
        item->setParam6(param6);
        item->setParam7(param7);
        item->setCommand(command);
        item->setFrame(frame);
        item->setAutoContinue(autoContinue);
        item->setSequenceNumber(seq);
        _missionItems.append(item);
    }

    if (_itemIndicesToRead.count() == 0) {
        _readTransactionComplete();
    } else {
        _requestNextMissionItem();
    }
}

void MissionController::_handleMissionAck(const mavlink_message_t &message)
{
    mavlink_mission_ack_t missionAck;
    mavlink_msg_mission_ack_decode(&message,&missionAck);

    AckType_t savedExpectedAck = _expectedAck;

    switch (savedExpectedAck) {
    case AckNone:
        // State machine is idle. Vehicle is confused.
        qDebug()<<"In handleMissionAck :Vehicle sent unexpected MISSION_ACK message";
        break;
//    case AckMissionCount:
//        // MISSION_COUNT message expected
//        // FIXME: Protocol error

//        break;
//    case AckMissionItem:
//        // MISSION_ITEM expected
//        // FIXME: Protocol error

//        break;
    case AckMissionRequest:
        // MISSION_REQUEST is expected, or MAV_MISSION_ACCEPTED to end sequence
        if (missionAck.type == MAV_MISSION_ACCEPTED){
            _finishedTransmit(true);
        }
        else{
            _finishedTransmit(false);
        }
        break;
    case AckMissionClearAll:
        // MAV_MISSION_ACCEPTED expected

        break;
//    case AckGuidedItem:
//        // MISSION_REQUEST is expected, or MAV_MISSION_ACCEPTED to end sequence

//        break;
    }


}

void MissionController::_finishedTransmit(bool succeed)
{
    disConnectFromMavlink();
    _ackTimeoutTimer->stop();
    if(succeed)
    {
        qDebug()<<"finish transmit";
        _writeMissionItems.clear();
    }
    else
    {
        qDebug()<<"transmit err";
        _writeMissionItems.clear();
    }
}

void MissionController::_startMissionTimeout(AckType_t ack)
{
    switch (ack) {
//    case AckMissionItem:
//        // We are actively trying to get the mission item, so we don't want to wait as long.
//        _ackTimeoutTimer->setInterval(_retryTimeoutMilliseconds);
//        break;
    case AckNone:
        // FALLTHROUGH
//    case AckMissionCount:
//        // FALLTHROUGH
    case AckMissionRequest:
        // FALLTHROUGH
    case AckMissionClearAll:
        _ackTimeoutTimer->setInterval(1500);
        break;
        // FALLTHROUGH
//    case AckGuidedItem:
//        _ackTimeoutTimer->setInterval(_ackTimeoutMilliseconds);
//        break;
    }

    _expectedAck = ack;
    _ackTimeoutTimer->start();
}



void MissionController::_ackTimeout()
{
    _ackTimeoutTimer->stop();
    switch (_expectedAck) {
    case AckNone:
        break;
    case AckMissionRequest:
        // MISSION_REQUEST is expected, or MISSION_ACK to end sequence
        _finishedTransmit(false);
        break;
    case AckMissionClearAll:
        // MISSION_ACK expected
        break;
    }
}

void MissionController::_mavlinkMessageReceived(const mavlink_message_t &msg)
{
    switch (msg.msgid) {
    case MAVLINK_MSG_ID_MISSION_COUNT:
        _handleMissionCount(msg);
        break;

    case MAVLINK_MSG_ID_MISSION_ITEM:
        _handleMissionItem(msg, false /* missionItemInt */);
        break;

    case MAVLINK_MSG_ID_MISSION_ITEM_INT:
        _handleMissionItem(msg, true /* missionItemInt */);
        break;

    case MAVLINK_MSG_ID_MISSION_REQUEST:
        _handleMissionRequest(msg, false /* missionItemInt */);
        qDebug()<<"MAVLINK_MSG_ID_MISSION_REQUEST";
        break;

    case MAVLINK_MSG_ID_MISSION_REQUEST_INT:
        //_handleMissionRequest(message, true /* missionItemInt */);
        qDebug()<<"MAVLINK_MSG_ID_MISSION_REQUEST_INT";
        break;

    case MAVLINK_MSG_ID_MISSION_ACK:
        _handleMissionAck(msg);
        break;
    }
}
