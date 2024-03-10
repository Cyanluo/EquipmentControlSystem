#ifndef PARAMETERMANAGER_H
#define PARAMETERMANAGER_H

#include "src/ECSToolbox.h"
#include "src/vehicle/vehicle.h"
#include "src/Fact/Fact.h"
#include <QMap>

class APMParameterMetaData;

class ParameterManager : public ECSTool
{
    Q_OBJECT
public:
    ParameterManager(ECSApplication* app, ECSToolbox* toolbox);

    void refreshAllParameters(uint8_t componentID = MAV_COMP_ID_ALL);
    void mavlinkMessageReceived(mavlink_message_t message);

    /// Returns the specified Parameter. Returns a default empty fact is parameter does not exists. Also will pop
    /// a missing parameter error to user if parameter does not exist.
    ///     @param componentId: Component id or FactSystem::defaultComponentId
    ///     @param name: Parameter name
    Fact* getParameter(int componentId, const QString& paramName);

    static MAV_PARAM_TYPE               factTypeToMavType(FactMetaData::ValueType_t factType);
    static FactMetaData::ValueType_t    mavTypeToFactType(MAV_PARAM_TYPE mavType);

signals:
    void factAdded                  (int componentId, Fact* fact);
    void parametersReadyChanged     (bool parametersReady);
    void missingParametersChanged   (bool missingParameters);

private:
    void    _waitingParamTimeout            (void);
    void    _initialRequestTimeout          (void);
    void    _handleParamValue               (int componentId, QString parameterName, int parameterCount, int parameterIndex, MAV_PARAM_TYPE mavParamType, QVariant parameterValue);
    void    _checkInitialLoadComplete       (void);
    bool    _fillIndexBatchQueue            (bool waitingParamTimeout);
    void    _readParameterRaw               (int componentId, const QString& paramName, int paramIndex);
    void    _sendParamSetToVehicle          (int componentId, const QString& paramName, FactMetaData::ValueType_t valueType, const QVariant& value);
    void    _factRawValueUpdated            (const QVariant& rawValue);
    void    _factRawValueUpdateWorker       (int componentId, const QString& name, FactMetaData::ValueType_t valueType, const QVariant& rawValue);

    APMParameterMetaData*   _apmMetaData    = nullptr;
    Vehicle*                _vehicle        = nullptr;

    QMap<int /* comp id */, QMap<QString /* parameter name */, Fact*>> _mapCompId2FactMap;

    QMap<int, int>                  _paramCountMap;             ///< Key: Component id, Value: count of parameters in this component
    QMap<int, QMap<int, int> >      _waitingReadParamIndexMap;  ///< Key: Component id, Value: Map { Key: parameter index still waiting for, Value: retry count }
    QMap<int, QMap<QString, int> >  _waitingReadParamNameMap;   ///< Key: Component id, Value: Map { Key: parameter name still waiting for, Value: retry count }
    QMap<int, QMap<QString, int> >  _waitingWriteParamNameMap;  ///< Key: Component id, Value: Map { Key: parameter name still waiting for, Value: retry count }
    QMap<int, QList<int> >          _failedReadParamIndexMap;   ///< Key: Component id, Value: failed parameter index

    QList<int>  _indexBatchQueue;       ///< The current queue of index re-requests
    bool        _indexBatchQueueActive; ///< true: we are actively batching re-requests for missing index base params, false: index based re-request has not yet started

    // Wait counts from previous parameter update cycle
    int _prevWaitingReadParamIndexCount;
    int _prevWaitingReadParamNameCount;
    int _prevWaitingWriteParamNameCount;

    int _totalParamCount;                       ///< Number of parameters across all components
    int _waitingWriteParamBatchCount = 0;       ///< Number of parameters which are batched up waiting on write responses
    int _waitingReadParamNameBatchCount = 0;    ///< Number of parameters which are batched up waiting on read responses
    bool        _initialLoadComplete;           ///< true: Initial load of all parameters complete, whether successful or not

    static const int    _maxReadWriteRetry = 5;                 ///< Maximum retries read/write
    static const int    _maxInitialLoadRetrySingleParam = 5;    ///< Maximum retries for initial index based load of a single param
    static const int    _maxInitialRequestListRetry = 4;        ///< Maximum retries for request list
    int                 _initialRequestRetryCount;              ///< Current retry count for request list
    bool                _disableAllRetries;                     ///< true: Don't retry any requests (used for testing)

    bool        _missingParameters;             ///< true: parameter missing from initial load
    bool        _parametersReady;               ///< true: parameter load complete

    Fact _defaultFact;   ///< Used to return default fact, when parameter not found

    QTimer _initialRequestTimeoutTimer;
    QTimer _waitingParamTimeoutTimer;
};

#endif // PARAMETERMANAGER_H
