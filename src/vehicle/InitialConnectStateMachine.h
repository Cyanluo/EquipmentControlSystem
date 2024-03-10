#ifndef INITIALCONNECTSTATEMACHINE_H
#define INITIALCONNECTSTATEMACHINE_H

#include "src/vehicle/StateMachine.h"

class Vehicle;

class InitialConnectStateMachine : public StateMachine
{
public:
    InitialConnectStateMachine(Vehicle* vehicle);

    // Overrides from StateMachine
    int             stateCount      (void) const final;
    const StateFn*  rgStates        (void) const final;
    void            statesCompleted (void) const final;

private:
    static void _stateRequestCompInfo                   (StateMachine* stateMachine);
    static void _stateRequestParameters                 (StateMachine* stateMachine);
    static void _stateRequestMission                    (StateMachine* stateMachine);
    Vehicle* _vehicle;

    static const StateFn    _rgStates[];
    static const int        _cStates;
};


#endif // INITIALCONNECTSTATEMACHINE_H
