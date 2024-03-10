#ifndef GLOBALQMLACESS_H
#define GLOBALQMLACESS_H

#include "ECSApplication.h"
#include "ECSToolbox.h"
#include "src/gcs_mavlink/gcs_mavlink.h"
#include "src/MissionManager/missioncontroller.h"
#include "src/ParameterManager/ParameterManager.h"

class GlobalQMLAcess: public ECSTool
{
    Q_OBJECT
public:
    Q_PROPERTY(GCS_Mavlink*             linkManager             READ    linkManager             CONSTANT)
    Q_PROPERTY(MissionController*       missionController       READ    missionController       CONSTANT)
    Q_PROPERTY(ParameterManager*        parameterManager        READ    parameterManager        CONSTANT)

    GlobalQMLAcess(ECSApplication* app, ECSToolbox* toolbox);

    void setToolbox(ECSToolbox* toolbox) override;

    GCS_Mavlink* linkManager() { return _linkManager; }
    MissionController* missionController() { return _missionController; }
    ParameterManager* parameterManager() { return _parameterManager; }

private:
    GCS_Mavlink* _linkManager = nullptr;
    MissionController* _missionController = nullptr;
    ParameterManager* _parameterManager = nullptr;
};

#endif // GLOBALQMLACESS_H
