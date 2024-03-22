#include "src/Fact/FactPanelController.h"
#include "src/ECSApplication.h"
#include "src/ParameterManager/ParameterManager.h"

#include <QQmlEngine>

FactPanelController::FactPanelController()
{
    _vehicle = ecsApp()->activeVehicle();

    _missingParametersTimer.setInterval(500);
    _missingParametersTimer.setSingleShot(true);
    connect(&_missingParametersTimer, &QTimer::timeout, this, &FactPanelController::_checkForMissingParameters);
}

void FactPanelController::_reportMissingParameter(int componentId, const QString& name)
{
    qDebug() << "Missing parameter:" << QString("%1:%2").arg(componentId).arg(name);
}

bool FactPanelController::_allParametersExists(int componentId, QStringList names)
{
    bool noMissingFacts = true;

    foreach (const QString &name, names) {
        if (ecsApp()->toolbox()->parameterManager()->parameterExists(componentId, name)) {
            _reportMissingParameter(componentId, name);
            noMissingFacts = false;
        }
    }

    return noMissingFacts;
}


Fact* FactPanelController::getParameterFact(int componentId, const QString& name, bool reportMissing)
{
    if (ecsApp()->toolbox()->parameterManager()->parameterExists(componentId, name)) {
        Fact* fact = ecsApp()->toolbox()->parameterManager()->getParameter(componentId, name);
        QQmlEngine::setObjectOwnership(fact, QQmlEngine::CppOwnership);
        return fact;
    } else {
        if (reportMissing) {
            _reportMissingParameter(componentId, name);
        }
        return nullptr;
    }
}

bool FactPanelController::parameterExists(int componentId, const QString& name)
{
    return ecsApp()->toolbox()->parameterManager()->parameterExists(componentId, name);
}

void FactPanelController::getMissingParameters(QStringList rgNames)
{
    for (const QString& name: rgNames) {
        _missingParameterWaitList.append(name);
        ecsApp()->toolbox()->parameterManager()->refreshParameter(MAV_COMP_ID_AUTOPILOT1, name);
    }

    _missingParametersTimer.start();
}

void FactPanelController::_checkForMissingParameters(void)
{
    QStringList waitList = _missingParameterWaitList;
    for (const QString& name: waitList) {
        if (ecsApp()->toolbox()->parameterManager()->parameterExists(MAV_COMP_ID_AUTOPILOT1, name)) {
            _missingParameterWaitList.removeOne(name);
        }
    }

    if (_missingParameterWaitList.isEmpty()) {
        emit missingParametersAvailable();
    } else {
        _missingParametersTimer.start();
    }
}
