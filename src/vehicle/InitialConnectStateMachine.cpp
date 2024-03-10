#include "src/vehicle/InitialConnectStateMachine.h"
#include "src/vehicle/vehicle.h"
#include "src/ECSApplication.h"
#include "src/MissionManager/missioncontroller.h"
#include "src/ParameterManager/ParameterManager.h"

#include <QDebug>

const StateMachine::StateFn InitialConnectStateMachine::_rgStates[] = {
    InitialConnectStateMachine::_stateRequestCompInfo,
    InitialConnectStateMachine::_stateRequestMission,
    InitialConnectStateMachine::_stateRequestParameters,
};

const int InitialConnectStateMachine::_cStates = sizeof(InitialConnectStateMachine::_rgStates) / sizeof(InitialConnectStateMachine::_rgStates[0]);

InitialConnectStateMachine::InitialConnectStateMachine(Vehicle* vehicle)
    : _vehicle(vehicle)
{
    connect(ecsApp()->toolbox()->missionController(), &MissionController::readComplete, this, &InitialConnectStateMachine::advance);
}

int InitialConnectStateMachine::stateCount(void) const
{
    return _cStates;
}

const InitialConnectStateMachine::StateFn* InitialConnectStateMachine::rgStates(void) const
{
    return &_rgStates[0];
}

void InitialConnectStateMachine::statesCompleted(void) const
{
    qDebug() << "InitialConnectStateMachine Complete";
}

void InitialConnectStateMachine::_stateRequestCompInfo(StateMachine* stateMachine)
{
    InitialConnectStateMachine* connectMachine  = static_cast<InitialConnectStateMachine*>(stateMachine);
    Vehicle*                    vehicle         = connectMachine->_vehicle;

    qDebug() << "sysid:" << vehicle->sysid() << " compid:" << vehicle->compid() << " type:" << vehicle->type();

    connectMachine->advance();
}

void InitialConnectStateMachine::_stateRequestMission(StateMachine* stateMachine)
{
    ecsApp()->toolbox()->missionController()->loadFromVehicle();
}

void InitialConnectStateMachine::_stateRequestParameters(StateMachine* stateMachine)
{
    InitialConnectStateMachine* connectMachine  = static_cast<InitialConnectStateMachine*>(stateMachine);

    ecsApp()->toolbox()->parameterManager()->refreshAllParameters(connectMachine->_vehicle->compid());
    qDebug() << "RequestParameters";

    connectMachine->advance();
}
