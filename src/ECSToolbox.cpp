#include "ECSToolbox.h"
#include "ECSApplication.h"
#include "src/MissionManager/missioncontroller.h"
#include "gcs_mavlink/gcs_mavlink.h"
#include "src/ParameterManager/ParameterManager.h"

ECSToolbox::ECSToolbox(ECSApplication *app)
{
    _linkManager        =   new GCS_Mavlink(app, this);
    _missionController  =   new MissionController(app, this);
    _parameterManager   =   new ParameterManager(app, this);
}

void ECSToolbox::setChildToolboxes(void)
{
    _linkManager->setToolbox(this);
    _missionController->setToolbox(this);
    _parameterManager->setToolbox(this);
}

ECSToolbox::~ECSToolbox()
{
    delete _linkManager;
    delete _missionController;
    delete _parameterManager;
}

ECSTool::ECSTool(ECSApplication* app, ECSToolbox* toolbox)
    : QObject(toolbox)
    , _app(app)
    , _toolbox(nullptr)
{

}

void ECSTool::setToolbox(ECSToolbox* toolbox)
{
    _toolbox = toolbox;
}
