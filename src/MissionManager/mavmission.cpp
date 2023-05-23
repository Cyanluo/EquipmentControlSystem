#include "mavmission.h"

MavMission::MavMission(QObject *parent)
    : QObject{parent}
{

}

void MavMission::setCommand(MAV_CMD command)
{
    _command = command;
}

void MavMission::setSequenceNumber(int sequenceNumber)
{
    _sequenceNumber = sequenceNumber;
}

void MavMission::setFrame(MAV_FRAME frame)
{
    _frame = frame;
}

void MavMission::setAutoContinue(bool autoContinue)
{
    _autoContinue = autoContinue;
}

void MavMission::setParam1(double param1)
{
    _param1 = param1;
}

void MavMission::setParam2(double param2)
{
    _param2 = param2;
}

void MavMission::setParam3(double param3)
{
    _param3 = param3;
}

void MavMission::setParam4(double param4)
{
    _param4 = param4;
}

void MavMission::setParam5(double param5)
{
    _param5 = param5;
}

void MavMission::setParam6(double param6)
{
    _param6 = param6;
}

void MavMission::setParam7(double param7)
{
    _param7 = param7;
}

