#include "src/ParameterManager/ParameterManager.h"
#include "src/ParameterManager/APMParameterMetaData.h"
#include "src/ECSApplication.h"

ParameterManager::ParameterManager(ECSApplication* app, ECSToolbox* toolbox)
    :ECSTool(app, toolbox)
    , _indexBatchQueueActive            (false)
    , _prevWaitingReadParamIndexCount   (0)
    , _prevWaitingReadParamNameCount    (0)
    , _prevWaitingWriteParamNameCount   (0)
    , _totalParamCount                  (0)
    , _initialLoadComplete              (false)
    , _initialRequestRetryCount         (0)
    , _disableAllRetries                (false)
    , _missingParameters                (false)
    , _parametersReady                  (false)
{
    _apmMetaData = new APMParameterMetaData();

    _initialRequestTimeoutTimer.setSingleShot(true);
    _initialRequestTimeoutTimer.setInterval(5000);
    connect(&_initialRequestTimeoutTimer, &QTimer::timeout, this, &ParameterManager::_initialRequestTimeout);

    _waitingParamTimeoutTimer.setSingleShot(true);
    _waitingParamTimeoutTimer.setInterval(3000);
    connect(&_waitingParamTimeoutTimer, &QTimer::timeout, this, &ParameterManager::_waitingParamTimeout);
}

void ParameterManager::refreshAllParameters(uint8_t componentId)
{
    if(_vehicle == nullptr) {
        _vehicle = ecsApp()->activeVehicle();
    }

    _apmMetaData->loadParameterFactMetaDataFile(":/APM/APMParameterFactMetaData.Rover.4.0.xml");

    if (!_initialLoadComplete) {
        _initialRequestTimeoutTimer.start();
    }

    // Reset index wait lists
    for (int cid: _paramCountMap.keys()) {
        // Add/Update all indices to the wait list, parameter index is 0-based
        if(componentId != MAV_COMP_ID_ALL && componentId != cid)
            continue;
        for (int waitingIndex = 0; waitingIndex < _paramCountMap[cid]; waitingIndex++) {
            // This will add a new waiting index if needed and set the retry count for that index to 0
            _waitingReadParamIndexMap[cid][waitingIndex] = 0;
        }
    }

    mavlink_message_t msg;
    mavlink_param_request_list_t param_rl;
    param_rl.target_component = 1;
    param_rl.target_system = 1;
    mavlink_msg_param_request_list_encode(254,
                                          1,
                                          &msg,
                                          &param_rl);
    uint8_t buff[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buff, &msg);
    _vehicle->my_mavlink->sendData((const char*)buff, len);

    QString what = (componentId == MAV_COMP_ID_ALL) ? "MAV_COMP_ID_ALL" : QString::number(componentId);
    qDebug() << "Request to refresh all parameters for component ID:" << what;
}

void ParameterManager::mavlinkMessageReceived(mavlink_message_t message)
{
    if (message.msgid == MAVLINK_MSG_ID_PARAM_VALUE) {
        mavlink_param_value_t param_value;
        mavlink_msg_param_value_decode(&message, &param_value);
        // This will null terminate the name string
        QByteArray bytes(param_value.param_id, MAVLINK_MSG_PARAM_VALUE_FIELD_PARAM_ID_LEN);
        QString parameterName(bytes);

        QVariant parameterValue;

        switch (param_value.param_type) {
        case MAV_PARAM_TYPE_UINT8:
            parameterValue = QVariant(static_cast<uint8_t>(param_value.param_value));
            break;
        case MAV_PARAM_TYPE_INT8:
            parameterValue  = QVariant(static_cast<int8_t>(param_value.param_value));
            break;
        case MAV_PARAM_TYPE_UINT16:
            parameterValue = QVariant(static_cast<uint16_t>(param_value.param_value));
            break;
        case MAV_PARAM_TYPE_INT16:
            parameterValue = QVariant(static_cast<int16_t>(param_value.param_value));
            break;
        case MAV_PARAM_TYPE_UINT32:
            parameterValue = QVariant(static_cast<uint32_t>(param_value.param_value));
            break;
        case MAV_PARAM_TYPE_INT32:
            parameterValue = QVariant(static_cast<int32_t>(param_value.param_value));
            break;
        case MAV_PARAM_TYPE_REAL32:
            parameterValue = QVariant(param_value.param_value);
            break;
        default:
            qDebug() << "Invalid/Unsupported data type used in parameter:" << param_value.param_type;
        }

        _handleParamValue(message.compid, parameterName, param_value.param_count, param_value.param_index, static_cast<MAV_PARAM_TYPE>(param_value.param_type), parameterValue);
    }
}

/// Called whenever a parameter is updated or first seen.
void ParameterManager::_handleParamValue(int componentId, QString parameterName, int parameterCount, int parameterIndex, MAV_PARAM_TYPE mavParamType, QVariant parameterValue)
{
    // ArduPilot has this strange behavior of streaming parameters that we didn't ask for. This even happens before it responds to the
    // PARAM_REQUEST_LIST. We disregard any of this until the initial request is responded to.
    if (parameterIndex == 65535 && parameterName != "_HASH_CHECK" && _initialRequestTimeoutTimer.isActive()) {
        if (!_waitingReadParamIndexMap[componentId].contains(parameterIndex) &&
            !_waitingReadParamNameMap[componentId].contains(parameterName) &&
            !_waitingWriteParamNameMap[componentId].contains(parameterName)) {
            return;
        }
        qDebug() << "Disregarding unrequested param prior to initial list response" << parameterName;
        return;
    }

    _initialRequestTimeoutTimer.stop();
    _waitingParamTimeoutTimer.stop();

    // Update our total parameter counts
    if (!_paramCountMap.contains(componentId)) {
        _paramCountMap[componentId] = parameterCount;
        _totalParamCount += parameterCount;
    }

    // If we've never seen this component id before, setup the index wait lists.
    if (!_waitingReadParamIndexMap.contains(componentId)) {
        // Add all indices to the wait list, parameter index is 0-based
        for (int waitingIndex=0; waitingIndex<parameterCount; waitingIndex++) {
            // This will add the new component id, as well as the the new waiting index and set the retry count for that index to 0
            _waitingReadParamIndexMap[componentId][waitingIndex] = 0;
        }

        // The read and write waiting lists for this component are initialized the empty
        _waitingReadParamNameMap[componentId] = QMap<QString, int>();
        _waitingWriteParamNameMap[componentId] = QMap<QString, int>();

        qDebug() << "Seeing component for first time - paramcount:" << parameterCount;
    }

    if (!_waitingReadParamIndexMap[componentId].contains(parameterIndex) &&
        !_waitingReadParamNameMap[componentId].contains(parameterName) &&
        !_waitingWriteParamNameMap[componentId].contains(parameterName)) {
        return;
    }

    qDebug() << "_parameterUpdate" <<
        "name:" << parameterName <<
        "count:" << parameterCount <<
        "index:" << parameterIndex <<
        "mavType:" << mavParamType <<
        "value:" << parameterValue <<
        ")";

    // Remove this parameter from the waiting lists
    if (_waitingReadParamIndexMap[componentId].contains(parameterIndex)) {
        _waitingReadParamIndexMap[componentId].remove(parameterIndex);
         _indexBatchQueue.removeOne(parameterIndex);
         _fillIndexBatchQueue(false /* waitingParamTimeout */);
    }
    _waitingReadParamNameMap[componentId].remove(parameterName);
    _waitingWriteParamNameMap[componentId].remove(parameterName);
//    if (_waitingReadParamIndexMap[componentId].count()) {
//        qCDebug(ParameterManagerVerbose2Log) << _logVehiclePrefix(componentId) << "_waitingReadParamIndexMap:" << _waitingReadParamIndexMap[componentId];
//    }
//    if (_waitingReadParamNameMap[componentId].count()) {
//        qCDebug(ParameterManagerVerbose2Log) << _logVehiclePrefix(componentId) << "_waitingReadParamNameMap" << _waitingReadParamNameMap[componentId];
//    }
//    if (_waitingWriteParamNameMap[componentId].count()) {
//        qCDebug(ParameterManagerVerbose2Log) << _logVehiclePrefix(componentId) << "_waitingWriteParamNameMap" << _waitingWriteParamNameMap[componentId];
//    }

    // Track how many parameters we are still waiting for

    int waitingReadParamIndexCount = 0;
    int waitingReadParamNameCount = 0;
    int waitingWriteParamNameCount = 0;

    for(int waitingComponentId: _waitingReadParamIndexMap.keys()) {
        waitingReadParamIndexCount += _waitingReadParamIndexMap[waitingComponentId].count();
    }
    if (waitingReadParamIndexCount) {
        qDebug() << "waitingReadParamIndexCount:" << waitingReadParamIndexCount;
    }

    for(int waitingComponentId: _waitingReadParamNameMap.keys()) {
        waitingReadParamNameCount += _waitingReadParamNameMap[waitingComponentId].count();
    }
    if (waitingReadParamNameCount) {
        qDebug() << "waitingReadParamNameCount:" << waitingReadParamNameCount;
    }

    for(int waitingComponentId: _waitingWriteParamNameMap.keys()) {
        waitingWriteParamNameCount += _waitingWriteParamNameMap[waitingComponentId].count();
    }
    if (waitingWriteParamNameCount) {
        qDebug() << "waitingWriteParamNameCount:" << waitingWriteParamNameCount;
    }

    int readWaitingParamCount = waitingReadParamIndexCount + waitingReadParamNameCount;
    int totalWaitingParamCount = readWaitingParamCount + waitingWriteParamNameCount;
    if (totalWaitingParamCount) {
        // More params to wait for, restart timer
        _waitingParamTimeoutTimer.start();
        qDebug() << "Restarting _waitingParamTimeoutTimer: totalWaitingParamCount:" << totalWaitingParamCount;
    } else {
        if (!_mapCompId2FactMap.contains(_vehicle->defaultCompid())) {
            // Still waiting for parameters from default component
            qDebug() << "Restarting _waitingParamTimeoutTimer (still waiting for default component params)";
            _waitingParamTimeoutTimer.start();
        } else {
            qDebug() << "Not restarting _waitingParamTimeoutTimer (all requests satisfied)";
        }
    }

    _updateProgressBar();

    Fact* fact = nullptr;
    if (_mapCompId2FactMap.contains(componentId) && _mapCompId2FactMap[componentId].contains(parameterName)) {
        fact = _mapCompId2FactMap[componentId][parameterName];
    } else {
        qDebug() << "Adding new fact" << parameterName;

        fact = new Fact(componentId, parameterName, mavTypeToFactType(mavParamType), this);
        FactMetaData* factMetaData = _apmMetaData->getMetaDataForFact(parameterName, _vehicle->type(), fact->type());
        fact->setMetaData(factMetaData);

        _mapCompId2FactMap[componentId][parameterName] = fact;

        // We need to know when the fact value changes so we can update the vehicle
        connect(fact, &Fact::_containerRawValueChanged, this, &ParameterManager::_factRawValueUpdated);

        emit factAdded(componentId, fact);
    }

    fact->_containerSetRawValue(parameterValue);

    _prevWaitingReadParamIndexCount = waitingReadParamIndexCount;
    _prevWaitingReadParamNameCount = waitingReadParamNameCount;
    _prevWaitingWriteParamNameCount = waitingWriteParamNameCount;

    _checkInitialLoadComplete();
}

/// Requests missing index based parameters from the vehicle.
///     @param waitingParamTimeout: true: being called due to timeout, false: being called to re-fill the batch queue
/// return true: Parameters were requested, false: No more requests needed
bool ParameterManager::_fillIndexBatchQueue(bool waitingParamTimeout)
{
    if (!_indexBatchQueueActive) {
        return false;
    }

    const int maxBatchSize = 10;

    if (waitingParamTimeout) {
        // We timed out, clear the queue and try again
        qDebug() << "Refilling index based batch queue due to timeout";
        _indexBatchQueue.clear();
    } else {
        qDebug() << "Refilling index based batch queue due to received parameter";
    }

    for(int componentId: _waitingReadParamIndexMap.keys()) {
        if (_waitingReadParamIndexMap[componentId].count()) {
            qDebug() <<  "_waitingReadParamIndexMap count" << _waitingReadParamIndexMap[componentId].count();
            qDebug() <<  "_waitingReadParamIndexMap" << _waitingReadParamIndexMap[componentId];
        }

        for(int paramIndex: _waitingReadParamIndexMap[componentId].keys()) {
            if (_indexBatchQueue.contains(paramIndex)) {
                // Don't add more than once
                continue;
            }

            if (_indexBatchQueue.count() > maxBatchSize) {
                break;
            }

            _waitingReadParamIndexMap[componentId][paramIndex]++;   // Bump retry count
            if (_disableAllRetries || _waitingReadParamIndexMap[componentId][paramIndex] > _maxInitialLoadRetrySingleParam) {
                // Give up on this index
                _failedReadParamIndexMap[componentId] << paramIndex;
                qDebug() << "Giving up on (paramIndex:" << paramIndex << "retryCount:" << _waitingReadParamIndexMap[componentId][paramIndex] << ")";
                _waitingReadParamIndexMap[componentId].remove(paramIndex);
            } else {
                // Retry again
                _indexBatchQueue.append(paramIndex);
                _readParameterRaw(componentId, "", paramIndex);
                qDebug() << "Read re-request for (paramIndex:" << paramIndex << "retryCount:" << _waitingReadParamIndexMap[componentId][paramIndex] << ")";
            }
        }
    }

    return _indexBatchQueue.count() != 0;
}

FactMetaData::ValueType_t ParameterManager::mavTypeToFactType(MAV_PARAM_TYPE mavType)
{
    switch (mavType) {
    case MAV_PARAM_TYPE_UINT8:
        return FactMetaData::valueTypeUint8;

    case MAV_PARAM_TYPE_INT8:
        return FactMetaData::valueTypeInt8;

    case MAV_PARAM_TYPE_UINT16:
        return FactMetaData::valueTypeUint16;

    case MAV_PARAM_TYPE_INT16:
        return FactMetaData::valueTypeInt16;

    case MAV_PARAM_TYPE_UINT32:
        return FactMetaData::valueTypeUint32;

    case MAV_PARAM_TYPE_UINT64:
        return FactMetaData::valueTypeUint64;

    case MAV_PARAM_TYPE_INT64:
        return FactMetaData::valueTypeInt64;

    case MAV_PARAM_TYPE_REAL32:
        return FactMetaData::valueTypeFloat;

    case MAV_PARAM_TYPE_REAL64:
        return FactMetaData::valueTypeDouble;

    default:
        qWarning() << "Unsupported mav param type" << mavType;
        // fall through

    case MAV_PARAM_TYPE_INT32:
        return FactMetaData::valueTypeInt32;
    }
}

MAV_PARAM_TYPE ParameterManager::factTypeToMavType(FactMetaData::ValueType_t factType)
{
    switch (factType) {
    case FactMetaData::valueTypeUint8:
        return MAV_PARAM_TYPE_UINT8;

    case FactMetaData::valueTypeInt8:
        return MAV_PARAM_TYPE_INT8;

    case FactMetaData::valueTypeUint16:
        return MAV_PARAM_TYPE_UINT16;

    case FactMetaData::valueTypeInt16:
        return MAV_PARAM_TYPE_INT16;

    case FactMetaData::valueTypeUint32:
        return MAV_PARAM_TYPE_UINT32;

    case FactMetaData::valueTypeUint64:
        return MAV_PARAM_TYPE_UINT64;

    case FactMetaData::valueTypeInt64:
        return MAV_PARAM_TYPE_INT64;

    case FactMetaData::valueTypeFloat:
        return MAV_PARAM_TYPE_REAL32;

    case FactMetaData::valueTypeDouble:
        return MAV_PARAM_TYPE_REAL64;

    default:
        qWarning() << "Unsupported fact type" << factType;
        // fall through

    case FactMetaData::valueTypeInt32:
        return MAV_PARAM_TYPE_INT32;
    }
}

void ParameterManager::_waitingParamTimeout(void)
{
    bool paramsRequested = false;
    const int maxBatchSize = 10;
    int batchCount = 0;

    qDebug() << "_waitingParamTimeout";

    // Now that we have timed out for possibly the first time we can activate the index batch queue
    _indexBatchQueueActive = true;

    // First check for any missing parameters from the initial index based load
    paramsRequested = _fillIndexBatchQueue(true /* waitingParamTimeout */);

    if (!paramsRequested && !_mapCompId2FactMap.contains(_vehicle->defaultCompid())) {
        // Initial load is complete but we still don't have any default component params. Wait one more cycle to see if the
        // any show up.
        qDebug() << "Restarting _waitingParamTimeoutTimer - still don't have default component params" << _vehicle->defaultCompid();
        _waitingParamTimeoutTimer.start();
        return;
    }

    _checkInitialLoadComplete();

    if (!paramsRequested) {
        for(int componentId: _waitingWriteParamNameMap.keys()) {
            for(const QString &paramName: _waitingWriteParamNameMap[componentId].keys()) {
                paramsRequested = true;
                _waitingWriteParamNameMap[componentId][paramName]++;   // Bump retry count
                if (_waitingWriteParamNameMap[componentId][paramName] <= _maxReadWriteRetry) {
                    Fact* fact = getParameter(componentId, paramName);
                    _sendParamSetToVehicle(componentId, paramName, fact->type(), fact->rawValue());
                    qDebug() << "Write resend for (paramName:" << paramName << "retryCount:" << _waitingWriteParamNameMap[componentId][paramName] << ")";
                    if (++batchCount > maxBatchSize) {
                        goto Out;
                    }
                } else {
                    // Exceeded max retry count, notify user
                    _waitingWriteParamNameMap[componentId].remove(paramName);
                    QString errorMsg = tr("Parameter write failed: veh:%1 comp:%2 param:%3").arg(_vehicle->sysid()).arg(componentId).arg(paramName);
                    qDebug() << errorMsg;
                }
            }
        }
    }

    if (!paramsRequested) {
        for(int componentId: _waitingReadParamNameMap.keys()) {
            for(const QString &paramName: _waitingReadParamNameMap[componentId].keys()) {
                paramsRequested = true;
                _waitingReadParamNameMap[componentId][paramName]++;   // Bump retry count
                if (_waitingReadParamNameMap[componentId][paramName] <= _maxReadWriteRetry) {
                    _readParameterRaw(componentId, paramName, -1);
                    qDebug() << "Read re-request for (paramName:" << paramName << "retryCount:" << _waitingReadParamNameMap[componentId][paramName] << ")";
                    if (++batchCount > maxBatchSize) {
                        goto Out;
                    }
                } else {
                    // Exceeded max retry count, notify user
                    _waitingReadParamNameMap[componentId].remove(paramName);
                    QString errorMsg = tr("Parameter read failed: veh:%1 comp:%2 param:%3").arg(_vehicle->sysid()).arg(componentId).arg(paramName);
                    qDebug() << errorMsg;
                }
            }
        }
    }

Out:
    if (paramsRequested) {
        qDebug() << "Restarting _waitingParamTimeoutTimer - re-request";
        _waitingParamTimeoutTimer.start();
    }
}

void ParameterManager::_sendParamSetToVehicle(int componentId, const QString& paramName, FactMetaData::ValueType_t valueType, const QVariant& value)
{
    mavlink_param_set_t     p;

    memset(&p, 0, sizeof(p));

    p.param_type = factTypeToMavType(valueType);
    p.param_value = value.toFloat();
    p.target_system = (uint8_t)_vehicle->sysid();
    p.target_component = (uint8_t)componentId;

    strncpy(p.param_id, paramName.toStdString().c_str(), sizeof(p.param_id));

    mavlink_message_t msg;
    mavlink_msg_param_set_encode(254,
                                 1,
                                 &msg,
                                 &p);
    uint8_t buff[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buff, &msg);
    _vehicle->my_mavlink->sendData((const char*)buff, len);
}

void ParameterManager::_initialRequestTimeout(void)
{
    if (!_disableAllRetries && ++_initialRequestRetryCount <= _maxInitialRequestListRetry) {
        qDebug() << "Retrying initial parameter request list";
        refreshAllParameters();
        _initialRequestTimeoutTimer.start();
    } else {
        QString errorMsg = tr("Vehicle %1 did not respond to request for parameters. ");
        qDebug() << errorMsg;
    }
}

void ParameterManager::_checkInitialLoadComplete(void)
{
    // Already processed?
    if (_initialLoadComplete) {
        return;
    }

    for (int componentId: _waitingReadParamIndexMap.keys()) {
        if (_waitingReadParamIndexMap[componentId].count()) {
            // We are still waiting on some parameters, not done yet
            return;
        }
    }

    if (!_mapCompId2FactMap.contains(_vehicle->defaultCompid())) {
        // No default component params yet, not done yet
        return;
    }

    // We aren't waiting for any more initial parameter updates, initial parameter loading is complete
    _initialLoadComplete = true;

    qDebug() << "Initial load complete";

    // Check for index based load failures
    QString indexList;
    bool initialLoadFailures = false;
    for (int componentId: _failedReadParamIndexMap.keys()) {
        for (int paramIndex: _failedReadParamIndexMap[componentId]) {
            if (initialLoadFailures) {
                indexList += ", ";
            }
            indexList += QString("%1:%2").arg(componentId).arg(paramIndex);
            initialLoadFailures = true;
            qDebug() << "Gave up on initial load after max retries (paramIndex:" << paramIndex << ")";
        }
    }

    _missingParameters = false;
    if (initialLoadFailures) {
        _missingParameters = true;
        QString errorMsg = tr("%1 was unable to retrieve the full set of parameters from vehicle %2. "
                              "This will cause %1 to be unable to display its full user interface. "
                              "If you are using modified firmware, you may need to resolve any vehicle startup errors to resolve the issue. "
                              "If you are using standard firmware, you may need to upgrade to a newer version to resolve the issue.").arg("ECSApplication").arg(_vehicle->defaultCompid());
        qDebug() << errorMsg;
    }

    // Signal load complete
    _parametersReady = true;
    emit parametersReadyChanged(true);
    emit missingParametersChanged(_missingParameters);
}

void ParameterManager::_readParameterRaw(int componentId, const QString& paramName, int paramIndex)
{
    mavlink_message_t       msg;
    mavlink_param_request_read_t param_request;

    strncpy(param_request.param_id, paramName.toStdString().c_str(), sizeof(param_request.param_id));
    param_request.target_system = _vehicle->sysid();
    param_request.target_component = componentId;
    param_request.param_index = paramIndex;

    mavlink_msg_param_request_read_encode(254,                 // ECS system id
                                            1,                 // ECS component id
                                            &msg,              // Pack into this mavlink_message_t
                                            &param_request);   // Parameter index being requested, -1 for named

    uint8_t buff[MAVLINK_MAX_PACKET_LEN];
    int len = mavlink_msg_to_send_buffer(buff, &msg);
    _vehicle->my_mavlink->sendData((const char*)buff, len);
}

Fact* ParameterManager::getParameter(int componentId, const QString& paramName)
{
    // QString mappedParamName = _remapParamNameToVersion(paramName);

    if (!_mapCompId2FactMap.contains(componentId) || !_mapCompId2FactMap[componentId].contains(paramName)) {
        return &_defaultFact;
    }

    return _mapCompId2FactMap[componentId][paramName];
}

void ParameterManager::_factRawValueUpdated(const QVariant& rawValue)
{
    Fact* fact = qobject_cast<Fact*>(sender());
    if (!fact) {
        qWarning() << "Internal error";
        return;
    }

    _factRawValueUpdateWorker(fact->componentId(), fact->name(), fact->type(), rawValue);
}

/// Writes the parameter update to mavlink, sets up for write wait
void ParameterManager::_factRawValueUpdateWorker(int componentId, const QString& name, FactMetaData::ValueType_t valueType, const QVariant& rawValue)
{
    if (_waitingWriteParamNameMap.contains(componentId)) {
        if (_waitingWriteParamNameMap[componentId].contains(name)) {
            _waitingWriteParamNameMap[componentId].remove(name);
        } else {
            _waitingWriteParamBatchCount++;
        }
        _waitingWriteParamNameMap[componentId][name] = 0; // Add new entry and set retry count
        // _updateProgressBar();
        _waitingParamTimeoutTimer.start();
    } else {
        qWarning() << "Internal error ParameterManager::_factValueUpdateWorker: component id not found" << componentId;
    }

    _sendParamSetToVehicle(componentId, name, valueType, rawValue);
    qDebug() << "Update parameter (_waitingParamTimeoutTimer started) - compId:name:rawValue" << componentId << name << rawValue;
}

void ParameterManager::_updateProgressBar(void)
{
    if(_initialLoadComplete) {
        return;
    }

    int waitingReadParamIndexCount = 0;

    for (int compId: _waitingReadParamIndexMap.keys()) {
        waitingReadParamIndexCount = _waitingReadParamIndexMap[compId].count();

        _setLoadProgress(compId, (double)(_paramCountMap[compId] - waitingReadParamIndexCount) / (double)_paramCountMap[compId]);
    }
}

void ParameterManager::_setLoadProgress(int componentId, double loadProgress)
{
    if (_loadProgress[componentId] != loadProgress) {
        _loadProgress[componentId] = loadProgress;
        emit loadProgressChanged(componentId, static_cast<float>(loadProgress));
    }
}
