#include "src/vehicle/InitialConnectStateMachine.h"
#include "src/vehicle/vehicle.h"
#include "src/ECSApplication.h"
#include "src/MissionManager/missioncontroller.h"
#include "src/ParameterManager/ParameterManager.h"

#include <QDebug>

const StateMachine::StateFn InitialConnectStateMachine::_rgStates[] = {
    InitialConnectStateMachine::_stateRequestCompInfo,
    InitialConnectStateMachine::_stateRequestParameters,
    InitialConnectStateMachine::_stateRequestMission,
};

const int InitialConnectStateMachine::_cStates = sizeof(InitialConnectStateMachine::_rgStates) / sizeof(InitialConnectStateMachine::_rgStates[0]);

InitialConnectStateMachine::InitialConnectStateMachine(Vehicle* vehicle)
    : _vehicle(vehicle)
{
    connect(ecsApp()->toolbox()->missionController(), &MissionController::readComplete, this, &InitialConnectStateMachine::missionReadComplete);
    connect(ecsApp()->toolbox()->parameterManager(), &ParameterManager::parametersReadyChanged, this, &InitialConnectStateMachine::parametersReadyChanged);

    _waitingMissionTimeoutTimer.setSingleShot(true);
    _waitingMissionTimeoutTimer.setInterval(3000);
    connect(&_waitingMissionTimeoutTimer, &QTimer::timeout, this, &InitialConnectStateMachine::_requestMission);
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

    qDebug() << "sysid:" << vehicle->sysid() << " compid:" << vehicle->defaultCompid() << " type:" << vehicle->type();

    connectMachine->advance();
}

void InitialConnectStateMachine::_stateRequestMission(StateMachine* stateMachine)
{
    InitialConnectStateMachine* connectMachine  = static_cast<InitialConnectStateMachine*>(stateMachine);

    qDebug() << "RequestMission";
    connectMachine->_requestMission();
}

void InitialConnectStateMachine::_stateRequestParameters(StateMachine* stateMachine)
{
    InitialConnectStateMachine* connectMachine  = static_cast<InitialConnectStateMachine*>(stateMachine);

    qDebug() << "RequestParameters";
    ecsApp()->toolbox()->parameterManager()->refreshAllParameters(connectMachine->_vehicle->defaultCompid());
}

void InitialConnectStateMachine::parametersReadyChanged(bool parametersReady)
{
    InitialConnectStateMachine* connectMachine  = static_cast<InitialConnectStateMachine*>(this);

    if(parametersReady) {
        connectMachine->advance();
        disconnect(ecsApp()->toolbox()->parameterManager(), &ParameterManager::parametersReadyChanged, this, &InitialConnectStateMachine::parametersReadyChanged);
    }
}

void InitialConnectStateMachine::missionReadComplete()
{
    InitialConnectStateMachine* connectMachine  = static_cast<InitialConnectStateMachine*>(this);

    _waitingMissionTimeoutTimer.stop();

    connectMachine->advance();
    disconnect(ecsApp()->toolbox()->missionController(), &MissionController::readComplete, this, &InitialConnectStateMachine::missionReadComplete);
}

void InitialConnectStateMachine::_requestMission()
{
    ecsApp()->toolbox()->missionController()->loadFromVehicle();

    _waitingMissionTimeoutTimer.start();
}
