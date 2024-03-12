#ifndef INITIALCONNECTSTATEMACHINE_H
#define INITIALCONNECTSTATEMACHINE_H

#include "src/vehicle/StateMachine.h"
#include <QTimer>

class Vehicle;

class InitialConnectStateMachine : public StateMachine
{
public:
    InitialConnectStateMachine(Vehicle* vehicle);

    // Overrides from StateMachine
    int             stateCount      (void) const final;
    const StateFn*  rgStates        (void) const final;
    void            statesCompleted (void) const final;

public slots:
    void parametersReadyChanged(bool parametersReady);
    void missionReadComplete();

private:    
    static void _stateRequestCompInfo                   (StateMachine* stateMachine);
    static void _stateRequestParameters                 (StateMachine* stateMachine);
    static void _stateRequestMission                    (StateMachine* stateMachine);

    void _requestMission();

    Vehicle* _vehicle;
    QTimer _waitingMissionTimeoutTimer;

    static const StateFn    _rgStates[];
    static const int        _cStates;
};


#endif // INITIALCONNECTSTATEMACHINE_H
