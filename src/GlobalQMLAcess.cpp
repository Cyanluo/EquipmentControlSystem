#include "GlobalQMLAcess.h"

GlobalQMLAcess::GlobalQMLAcess(ECSApplication* app, ECSToolbox* toolbox)
    : ECSTool(app, toolbox)
{

}

void GlobalQMLAcess::setToolbox(ECSToolbox* toolbox)
{
    ECSTool::setToolbox(toolbox);

    _linkManager = toolbox->linkManager();
    _missionController = toolbox->missionController();
    _parameterManager = toolbox->parameterManager();
}
