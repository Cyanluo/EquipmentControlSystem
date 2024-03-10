#include "src/Fact/FactMetaData.h"
#include <QtMath>
#include <limits>
#include <cmath>
#include <ardupilotmega/mavlink.h>

// Conversion Constants
// Time
const qreal FactMetaData::UnitConsts_s::secondsPerHour = 3600.0;

// Velocity
const qreal FactMetaData::UnitConsts_s::knotsToKPH = 1.852; // exact, hence weird base for knotsToMetersPerSecond

// Length
const qreal FactMetaData::UnitConsts_s::milesToMeters       = 1609.344;
const qreal FactMetaData::UnitConsts_s::feetToMeters        = 0.3048;
const qreal FactMetaData::UnitConsts_s::inchesToCentimeters = 2.54;

//Weight
const qreal FactMetaData::UnitConsts_s::ouncesToGrams = 28.3495;
const qreal FactMetaData::UnitConsts_s::poundsToGrams = 453.592;

const char* FactMetaData::kDefaultCategory = QT_TRANSLATE_NOOP("FactMetaData", "Other");
const char* FactMetaData::kDefaultGroup    = QT_TRANSLATE_NOOP("FactMetaData", "Misc");

// Built in translations for all Facts
const FactMetaData::BuiltInTranslation_s FactMetaData::_rgBuiltInTranslations[] = {
    { "centi-degrees",  "deg",  FactMetaData::_centiDegreesToDegrees,                   FactMetaData::_degreesToCentiDegrees },
    { "radians",        "deg",  FactMetaData::_radiansToDegrees,                        FactMetaData::_degreesToRadians },
    { "rad",            "deg",  FactMetaData::_radiansToDegrees,                        FactMetaData::_degreesToRadians },
    { "gimbal-degrees", "deg",  FactMetaData::_mavlinkGimbalDegreesToUserGimbalDegrees, FactMetaData::_userGimbalDegreesToMavlinkGimbalDegrees },
    { "norm",           "%",    FactMetaData::_normToPercent,                           FactMetaData::_percentToNorm },
    };

const char* FactMetaData::_rgKnownTypeStrings[] = {
    "Uint8",
    "Int8",
    "Uint16",
    "Int16",
    "Uint32",
    "Int32",
    "Uint64",
    "Int64",
    "Float",
    "Double",
    "String",
    "Bool",
    "ElapsedSeconds",
    "Custom",
};

const  FactMetaData::ValueType_t FactMetaData::_rgKnownValueTypes[] = {
    valueTypeUint8,
    valueTypeInt8,
    valueTypeUint16,
    valueTypeInt16,
    valueTypeUint32,
    valueTypeInt32,
    valueTypeUint64,
    valueTypeInt64,
    valueTypeFloat,
    valueTypeDouble,
    valueTypeString,
    valueTypeBool,
    valueTypeElapsedTimeInSeconds,
    valueTypeCustom,
};

FactMetaData::FactMetaData(QObject* parent)
    : QObject               (parent)
    , _type                 (valueTypeInt32)
    , _decimalPlaces        (kUnknownDecimalPlaces)
    , _rawDefaultValue      (0)
    , _defaultValueAvailable(false)
    , _rawMax               (_maxForType())
    , _maxIsDefaultForType  (true)
    , _rawMin               (_minForType())
    , _minIsDefaultForType  (true)
    , _rawTranslator        (_defaultTranslator)
    , _cookedTranslator     (_defaultTranslator)
    , _vehicleRebootRequired(false)
    , _qgcRebootRequired    (false)
    , _rawIncrement         (std::numeric_limits<double>::quiet_NaN())
    , _hasControl           (true)
    , _readOnly             (false)
    , _writeOnly            (false)
    , _volatile             (false)
{
    _category   = kDefaultCategory;
    _group      = kDefaultGroup;
}

FactMetaData::FactMetaData(ValueType_t type, QObject* parent)
    : QObject               (parent)
    , _type                 (type)
    , _decimalPlaces        (kUnknownDecimalPlaces)
    , _rawDefaultValue      (0)
    , _defaultValueAvailable(false)
    , _rawMax               (_maxForType())
    , _maxIsDefaultForType  (true)
    , _rawMin               (_minForType())
    , _minIsDefaultForType  (true)
    , _rawTranslator        (_defaultTranslator)
    , _cookedTranslator     (_defaultTranslator)
    , _vehicleRebootRequired(false)
    , _qgcRebootRequired    (false)
    , _rawIncrement         (std::numeric_limits<double>::quiet_NaN())
    , _hasControl           (true)
    , _readOnly             (false)
    , _writeOnly            (false)
    , _volatile             (false)
{
    _category   = kDefaultCategory;
    _group      = kDefaultGroup;
}

FactMetaData::FactMetaData(const FactMetaData& other, QObject* parent)
    : QObject(parent)
{
    *this = other;
}

FactMetaData::FactMetaData(ValueType_t type, const QString name, QObject* parent)
    : QObject               (parent)
    , _type                 (type)
    , _decimalPlaces        (kUnknownDecimalPlaces)
    , _rawDefaultValue      (0)
    , _defaultValueAvailable(false)
    , _rawMax               (_maxForType())
    , _maxIsDefaultForType  (true)
    , _rawMin               (_minForType())
    , _minIsDefaultForType  (true)
    , _name                 (name)
    , _rawTranslator        (_defaultTranslator)
    , _cookedTranslator     (_defaultTranslator)
    , _vehicleRebootRequired(false)
    , _qgcRebootRequired    (false)
    , _rawIncrement         (std::numeric_limits<double>::quiet_NaN())
    , _hasControl           (true)
    , _readOnly             (false)
    , _writeOnly            (false)
    , _volatile             (false)
{
    _category   = kDefaultCategory;
    _group      = kDefaultGroup;
}

const FactMetaData& FactMetaData::operator=(const FactMetaData& other)
{
    _decimalPlaces          = other._decimalPlaces;
    _rawDefaultValue        = other._rawDefaultValue;
    _defaultValueAvailable  = other._defaultValueAvailable;
    _bitmaskStrings         = other._bitmaskStrings;
    _bitmaskValues          = other._bitmaskValues;
    _enumStrings            = other._enumStrings;
    _enumValues             = other._enumValues;
    _category               = other._category;
    _group                  = other._group;
    _longDescription        = other._longDescription;
    _rawMax                 = other._rawMax;
    _maxIsDefaultForType    = other._maxIsDefaultForType;
    _rawMin                 = other._rawMin;
    _minIsDefaultForType    = other._minIsDefaultForType;
    _name                   = other._name;
    _shortDescription       = other._shortDescription;
    _type                   = other._type;
    _rawUnits               = other._rawUnits;
    _cookedUnits            = other._cookedUnits;
    _rawTranslator          = other._rawTranslator;
    _cookedTranslator       = other._cookedTranslator;
    _vehicleRebootRequired  = other._vehicleRebootRequired;
    _qgcRebootRequired      = other._qgcRebootRequired;
    _rawIncrement           = other._rawIncrement;
    _hasControl             = other._hasControl;
    _readOnly               = other._readOnly;
    _writeOnly              = other._writeOnly;
    _volatile               = other._volatile;
    return *this;
}

const QString FactMetaData::defaultGroup()
{
    return QString(kDefaultGroup);
}

const QString FactMetaData::defaultCategory()
{
    return QString(kDefaultCategory);
}

QVariant FactMetaData::rawDefaultValue(void) const
{
    if (_defaultValueAvailable) {
        return _rawDefaultValue;
    } else {
        qWarning() << "Attempt to access unavailable default value";
        return QVariant(0);
    }
}

void FactMetaData::setRawDefaultValue(const QVariant& rawDefaultValue)
{
    if (_type == valueTypeString || (isInRawMinLimit(rawDefaultValue) && isInRawMaxLimit(rawDefaultValue))) {
        _rawDefaultValue = rawDefaultValue;
        _defaultValueAvailable = true;
    } else {
        qWarning() << "Attempt to set default value which is outside min/max range";
    }
}

void FactMetaData::setRawMin(const QVariant& rawMin)
{
    if (isInRawMinLimit(rawMin)) {
        _rawMin = rawMin;
        _minIsDefaultForType = false;
    } else {
        qWarning() << "Attempt to set min below allowable value for fact: " << name()
                   << ", value attempted: " << rawMin
                   << ", type: " << type() << ", min for type: " << _minForType();
        _rawMin = _minForType();
    }
}

void FactMetaData::setRawMax(const QVariant& rawMax)
{
    if (isInRawMaxLimit(rawMax)) {
        _rawMax = rawMax;
        _maxIsDefaultForType = false;
    } else {
        qWarning() << "Attempt to set max above allowable value";
        _rawMax = _maxForType();
    }
}

bool FactMetaData::isInRawMinLimit(const QVariant& variantValue) const
{
    switch (_type) {
    case valueTypeUint8:
        return _rawMin.value<unsigned char>() <= variantValue.value<unsigned char>();
    case valueTypeInt8:
        return _rawMin.value<signed char>() <= variantValue.value<signed char>();
    case valueTypeUint16:
        return _rawMin.value<unsigned short int>() <= variantValue.value<unsigned short int>();
    case valueTypeInt16:
        return _rawMin.value<short int>() <= variantValue.value<short int>();
    case valueTypeUint32:
        return _rawMin.value<uint32_t>() <= variantValue.value<uint32_t>();
    case valueTypeInt32:
        return _rawMin.value<int32_t>() <= variantValue.value<int32_t>();
    case valueTypeUint64:
        return _rawMin.value<uint64_t>() <= variantValue.value<uint64_t>();
    case valueTypeInt64:
        return _rawMin.value<int64_t>() <= variantValue.value<int64_t>();
    case valueTypeFloat:
        return qIsNaN(variantValue.toFloat()) || _rawMin.value<float>() <= variantValue.value<float>();
    case valueTypeDouble:
        return qIsNaN(variantValue.toDouble()) || _rawMin.value<double>() <= variantValue.value<double>();
    default:
        return true;
    }

    return true;
}

bool FactMetaData::isInRawMaxLimit(const QVariant& variantValue) const
{
    switch (_type) {
    case valueTypeUint8:
        return _rawMax.value<unsigned char>() >= variantValue.value<unsigned char>();
    case valueTypeInt8:
        return _rawMax.value<signed char>() >= variantValue.value<signed char>();
    case valueTypeUint16:
        return _rawMax.value<unsigned short int>() >= variantValue.value<unsigned short int>();
    case valueTypeInt16:
        return _rawMax.value<short int>() >= variantValue.value<short int>();
    case valueTypeUint32:
        return _rawMax.value<uint32_t>() >= variantValue.value<uint32_t>();
    case valueTypeInt32:
        return _rawMax.value<int32_t>() >= variantValue.value<int32_t>();
    case valueTypeUint64:
        return _rawMax.value<uint64_t>() >= variantValue.value<uint64_t>();
    case valueTypeInt64:
        return _rawMax.value<int64_t>() >= variantValue.value<int64_t>();
    case valueTypeFloat:
        return qIsNaN(variantValue.toFloat()) || _rawMax.value<float>() >= variantValue.value<float>();
    case valueTypeDouble:
        return qIsNaN(variantValue.toDouble()) || _rawMax.value<double>() >= variantValue.value<double>();
    default:
        return true;
    }

    return true;
}

QVariant FactMetaData::_minForType(void) const
{
    switch (_type) {
    case valueTypeUint8:
        return QVariant(std::numeric_limits<unsigned char>::min());
    case valueTypeInt8:
        return QVariant(std::numeric_limits<signed char>::min());
    case valueTypeUint16:
        return QVariant(std::numeric_limits<unsigned short int>::min());
    case valueTypeInt16:
        return QVariant(std::numeric_limits<short int>::min());
    case valueTypeUint32:
        return QVariant(std::numeric_limits<uint32_t>::min());
    case valueTypeInt32:
        return QVariant(std::numeric_limits<int32_t>::min());
    case valueTypeUint64:
        return QVariant((qulonglong)std::numeric_limits<uint64_t>::min());
    case valueTypeInt64:
        return QVariant((qlonglong)std::numeric_limits<int64_t>::min());
    case valueTypeFloat:
        return QVariant(-std::numeric_limits<float>::max());
    case valueTypeDouble:
        return QVariant(-std::numeric_limits<double>::max());
    case valueTypeString:
        return QVariant();
    case valueTypeBool:
        return QVariant(0);
    case valueTypeElapsedTimeInSeconds:
        return QVariant(0.0);
    case valueTypeCustom:
        return QVariant();
    }

    // Make windows compiler happy, even switch is full cased
    return QVariant();
}

QVariant FactMetaData::_maxForType(void) const
{
    switch (_type) {
    case valueTypeUint8:
        return QVariant(std::numeric_limits<unsigned char>::max());
    case valueTypeInt8:
        return QVariant(std::numeric_limits<signed char>::max());
    case valueTypeUint16:
        return QVariant(std::numeric_limits<unsigned short int>::max());
    case valueTypeInt16:
        return QVariant(std::numeric_limits<short int>::max());
    case valueTypeUint32:
        return QVariant(std::numeric_limits<uint32_t>::max());
    case valueTypeInt32:
        return QVariant(std::numeric_limits<int32_t>::max());
    case valueTypeUint64:
        return QVariant((qulonglong)std::numeric_limits<uint64_t>::max());
    case valueTypeInt64:
        return QVariant((qlonglong)std::numeric_limits<int64_t>::max());
    case valueTypeFloat:
        return QVariant(std::numeric_limits<float>::max());
    case valueTypeElapsedTimeInSeconds:
    case valueTypeDouble:
        return QVariant(std::numeric_limits<double>::max());
    case valueTypeString:
        return QVariant();
    case valueTypeBool:
        return QVariant(1);
    case valueTypeCustom:
        return QVariant();
    }

    // Make windows compiler happy, even switch is full cased
    return QVariant();
}

bool FactMetaData::convertAndValidateRaw(const QVariant& rawValue, bool convertOnly, QVariant& typedValue, QString& errorString)
{
    bool convertOk = false;

    errorString.clear();

    switch (type()) {
    case FactMetaData::valueTypeInt8:
    case FactMetaData::valueTypeInt16:
    case FactMetaData::valueTypeInt32:
        typedValue = QVariant(rawValue.toInt(&convertOk));
        if (!convertOnly && convertOk) {
            if (!isInRawLimit<int32_t>(typedValue)) {
                errorString = tr("Value must be within %1 and %2").arg(rawMin().toInt()).arg(rawMax().toInt());
            }
        }
        break;
    case FactMetaData::valueTypeInt64:
        typedValue = QVariant(rawValue.toLongLong(&convertOk));
        if (!convertOnly && convertOk) {
            if (!isInRawLimit<int64_t>(typedValue)) {
                errorString = tr("Value must be within %1 and %2").arg(rawMin().toInt()).arg(rawMax().toInt());
            }
        }
        break;
    case FactMetaData::valueTypeUint8:
    case FactMetaData::valueTypeUint16:
    case FactMetaData::valueTypeUint32:
        typedValue = QVariant(rawValue.toUInt(&convertOk));
        if (!convertOnly && convertOk) {
            if (!isInRawLimit<uint32_t>(typedValue)) {
                errorString = tr("Value must be within %1 and %2").arg(rawMin().toUInt()).arg(rawMax().toUInt());
            }
        }
        break;
    case FactMetaData::valueTypeUint64:
        typedValue = QVariant(rawValue.toULongLong(&convertOk));
        if (!convertOnly && convertOk) {
            if (!isInRawLimit<uint64_t>(typedValue)) {
                errorString = tr("Value must be within %1 and %2").arg(rawMin().toUInt()).arg(rawMax().toUInt());
            }
        }
        break;
    case FactMetaData::valueTypeFloat:
        typedValue = QVariant(rawValue.toFloat(&convertOk));
        if (!convertOnly && convertOk) {
            if (!isInRawLimit<float>(typedValue)) {
                errorString = tr("Value must be within %1 and %2").arg(rawMin().toDouble()).arg(rawMax().toDouble());
            }
        }
        break;
    case FactMetaData::valueTypeElapsedTimeInSeconds:
    case FactMetaData::valueTypeDouble:
        typedValue = QVariant(rawValue.toDouble(&convertOk));
        if (!convertOnly && convertOk) {
            if (!isInRawLimit<double>(typedValue)) {
                errorString = tr("Value must be within %1 and %2").arg(rawMin().toDouble()).arg(rawMax().toDouble());
            }
        }
        break;
    case FactMetaData::valueTypeString:
        convertOk = true;
        typedValue = QVariant(rawValue.toString());
        break;
    case FactMetaData::valueTypeBool:
        convertOk = true;
        typedValue = QVariant(rawValue.toBool());
        break;
    case FactMetaData::valueTypeCustom:
        convertOk = true;
        typedValue = QVariant(rawValue.toByteArray());
        break;
    }

    if (!convertOk) {
        errorString += tr("Invalid number");
    }

    return convertOk && errorString.isEmpty();
}

bool FactMetaData::convertAndValidateCooked(const QVariant& cookedValue, bool convertOnly, QVariant& typedValue, QString& errorString)
{
    bool convertOk = false;

    errorString.clear();

    if (!convertOnly && _customCookedValidator) {
        errorString = _customCookedValidator(cookedValue);
        if (!errorString.isEmpty()) {
            return false;
        }
    }

    switch (type()) {
    case FactMetaData::valueTypeInt8:
    case FactMetaData::valueTypeInt16:
    case FactMetaData::valueTypeInt32:
        typedValue = QVariant(cookedValue.toInt(&convertOk));
        if (!convertOnly && convertOk) {
            if (!isInCookedLimit<int32_t>(typedValue)) {
                errorString = tr("Value must be within %1 and %2").arg(cookedMin().toInt()).arg(cookedMax().toInt());
            }
        }
        break;
    case FactMetaData::valueTypeInt64:
        typedValue = QVariant(cookedValue.toLongLong(&convertOk));
        if (!convertOnly && convertOk) {
            if (!isInCookedLimit<int64_t>(typedValue)) {
                errorString = tr("Value must be within %1 and %2").arg(cookedMin().toInt()).arg(cookedMax().toInt());
            }
        }
        break;
    case FactMetaData::valueTypeUint8:
    case FactMetaData::valueTypeUint16:
    case FactMetaData::valueTypeUint32:
        typedValue = QVariant(cookedValue.toUInt(&convertOk));
        if (!convertOnly && convertOk) {
            if (!isInCookedLimit<uint32_t>(typedValue)) {
                errorString = tr("Value must be within %1 and %2").arg(cookedMin().toUInt()).arg(cookedMax().toUInt());
            }
        }
        break;
    case FactMetaData::valueTypeUint64:
        typedValue = QVariant(cookedValue.toULongLong(&convertOk));
        if (!convertOnly && convertOk) {
            if (!isInCookedLimit<uint64_t>(typedValue)) {
                errorString = tr("Value must be within %1 and %2").arg(cookedMin().toUInt()).arg(cookedMax().toUInt());
            }
        }
        break;
    case FactMetaData::valueTypeFloat:
        typedValue = QVariant(cookedValue.toFloat(&convertOk));
        if (!convertOnly && convertOk) {
            if (!isInCookedLimit<float>(typedValue)) {
                errorString = tr("Value must be within %1 and %2").arg(cookedMin().toFloat()).arg(cookedMax().toFloat());
            }
        }
        break;
    case FactMetaData::valueTypeElapsedTimeInSeconds:
    case FactMetaData::valueTypeDouble:
        typedValue = QVariant(cookedValue.toDouble(&convertOk));
        if (!convertOnly && convertOk) {
            if (!isInCookedLimit<double>(typedValue)) {
                errorString = tr("Value must be within %1 and %2").arg(cookedMin().toDouble()).arg(cookedMax().toDouble());
            }
        }
        break;
    case FactMetaData::valueTypeString:
        convertOk = true;
        typedValue = QVariant(cookedValue.toString());
        break;
    case FactMetaData::valueTypeBool:
        convertOk = true;
        typedValue = QVariant(cookedValue.toBool());
        break;
    case FactMetaData::valueTypeCustom:
        convertOk = true;
        typedValue = QVariant(cookedValue.toByteArray());
        break;
    }

    if (!convertOk) {
        errorString += tr("Invalid number");
    }

    return convertOk && errorString.isEmpty();
}

bool FactMetaData::clampValue(const QVariant& cookedValue, QVariant& typedValue)
{
    bool convertOk = false;
    switch (type()) {
    case FactMetaData::valueTypeInt8:
    case FactMetaData::valueTypeInt16:
    case FactMetaData::valueTypeInt32:
        typedValue = QVariant(cookedValue.toInt(&convertOk));
        if (convertOk) {
            clamp<int32_t>(typedValue);
        }
        break;
    case FactMetaData::valueTypeInt64:
        typedValue = QVariant(cookedValue.toLongLong(&convertOk));
        if (convertOk) {
            clamp<int64_t>(typedValue);
        }
        break;
    case FactMetaData::valueTypeUint8:
    case FactMetaData::valueTypeUint16:
    case FactMetaData::valueTypeUint32:
        typedValue = QVariant(cookedValue.toUInt(&convertOk));
        if (convertOk) {
            clamp<uint32_t>(typedValue);
        }
        break;
    case FactMetaData::valueTypeUint64:
        typedValue = QVariant(cookedValue.toULongLong(&convertOk));
        if (convertOk) {
            clamp<uint64_t>(typedValue);
        }
        break;
    case FactMetaData::valueTypeFloat:
        typedValue = QVariant(cookedValue.toFloat(&convertOk));
        if (convertOk) {
            clamp<float>(typedValue);
        }
        break;
    case FactMetaData::valueTypeElapsedTimeInSeconds:
    case FactMetaData::valueTypeDouble:
        typedValue = QVariant(cookedValue.toDouble(&convertOk));
        if (convertOk) {
            clamp<double>(typedValue);
        }
        break;
    case FactMetaData::valueTypeString:
        convertOk = true;
        typedValue = QVariant(cookedValue.toString());
        break;
    case FactMetaData::valueTypeBool:
        convertOk = true;
        typedValue = QVariant(cookedValue.toBool());
        break;
    case FactMetaData::valueTypeCustom:
        convertOk = true;
        typedValue = QVariant(cookedValue.toByteArray());
        break;
    }
    return convertOk;
}

void FactMetaData::setBitmaskInfo(const QStringList& strings, const QVariantList& values)
{
    if (strings.count() != values.count()) {
        qWarning() << "Count mismatch strings:values" << strings.count() << values.count();
        return;
    }

    _bitmaskStrings = strings;
    _bitmaskValues = values;
    setBuiltInTranslator();
}

void FactMetaData::addBitmaskInfo(const QString& name, const QVariant& value)
{
    _bitmaskStrings << name;
    _bitmaskValues << value;
}

void FactMetaData::setEnumInfo(const QStringList& strings, const QVariantList& values)
{
    if (strings.count() != values.count()) {
        qWarning() << "Count mismatch strings:values" << strings.count() << values.count();
        return;
    }

    _enumStrings = strings;
    _enumValues = values;
    setBuiltInTranslator();
}

void FactMetaData::addEnumInfo(const QString& name, const QVariant& value)
{
    _enumStrings << name;
    _enumValues << value;
}

void FactMetaData::removeEnumInfo(const QVariant& value)
{
    const int index = _enumValues.indexOf(value);
    if (index < 0) {
        qWarning() << "Value does not exist in fact:" << value;
        return;
    }

    _enumValues.removeAt(index);
    _enumStrings.removeAt(index);
}

void FactMetaData::setTranslators(Translator rawTranslator, Translator cookedTranslator)
{
    _rawTranslator = rawTranslator;
    _cookedTranslator = cookedTranslator;
}

void FactMetaData::setBuiltInTranslator(void)
{
    if (_enumStrings.count() || _bitmaskStrings.count()) {
        // No translation if enum
        setTranslators(_defaultTranslator, _defaultTranslator);
        _cookedUnits = _rawUnits;
        return;
    } else {
        for (size_t i=0; i<sizeof(_rgBuiltInTranslations)/sizeof(_rgBuiltInTranslations[0]); i++) {
            const BuiltInTranslation_s* pBuiltInTranslation = &_rgBuiltInTranslations[i];

            if (pBuiltInTranslation->rawUnits.toLower() == _rawUnits.toLower()) {
                _cookedUnits = pBuiltInTranslation->cookedUnits;
                setTranslators(pBuiltInTranslation->rawTranslator, pBuiltInTranslation->cookedTranslator);
                return;
            }
        }
    }
}

QVariant FactMetaData::_degreesToRadians(const QVariant& degrees)
{
    return QVariant(qDegreesToRadians(degrees.toDouble()));
}

QVariant FactMetaData::_radiansToDegrees(const QVariant& radians)
{
    return QVariant(qRadiansToDegrees(radians.toDouble()));
}

QVariant FactMetaData::_centiDegreesToDegrees(const QVariant& centiDegrees)
{
    return QVariant(centiDegrees.toReal() / 100.0);
}

QVariant FactMetaData::_degreesToCentiDegrees(const QVariant& degrees)
{
    return QVariant(qRound(degrees.toReal() * 100.0));
}

QVariant FactMetaData::_userGimbalDegreesToMavlinkGimbalDegrees(const QVariant& userGimbalDegrees)
{
    // User facing gimbal degree values are from 0 (level) to 90 (straight down)
    // Mavlink gimbal degree values are from 0 (level) to -90 (straight down)
    return userGimbalDegrees.toDouble() * -1.0;
}

QVariant FactMetaData::_mavlinkGimbalDegreesToUserGimbalDegrees(const QVariant& mavlinkGimbalDegrees)
{
    // User facing gimbal degree values are from 0 (level) to 90 (straight down)
    // Mavlink gimbal degree values are from 0 (level) to -90 (straight down)
    return mavlinkGimbalDegrees.toDouble() * -1.0;
}

QVariant FactMetaData::_metersToFeet(const QVariant& meters)
{
    return QVariant(meters.toDouble() * 1.0/constants.feetToMeters);
}

QVariant FactMetaData::_feetToMeters(const QVariant& feet)
{
    return QVariant(feet.toDouble() * constants.feetToMeters);
}

QVariant FactMetaData::_squareMetersToSquareKilometers(const QVariant& squareMeters)
{
    return QVariant(squareMeters.toDouble() * 0.000001);
}

QVariant FactMetaData::_squareKilometersToSquareMeters(const QVariant& squareKilometers)
{
    return QVariant(squareKilometers.toDouble() * 1000000.0);
}

QVariant FactMetaData::_squareMetersToHectares(const QVariant& squareMeters)
{
    return QVariant(squareMeters.toDouble() * 0.0001);
}

QVariant FactMetaData::_hectaresToSquareMeters(const QVariant& hectares)
{
    return QVariant(hectares.toDouble() * 1000.0);
}

QVariant FactMetaData::_squareMetersToSquareFeet(const QVariant& squareMeters)
{
    return QVariant(squareMeters.toDouble() * 10.7639);
}

QVariant FactMetaData::_squareFeetToSquareMeters(const QVariant& squareFeet)
{
    return QVariant(squareFeet.toDouble() * 0.0929);
}

QVariant FactMetaData::_squareMetersToAcres(const QVariant& squareMeters)
{
    return QVariant(squareMeters.toDouble() * 0.000247105);
}

QVariant FactMetaData::_acresToSquareMeters(const QVariant& acres)
{
    return QVariant(acres.toDouble() * 4046.86);
}

QVariant FactMetaData::_squareMetersToSquareMiles(const QVariant& squareMeters)
{
    return QVariant(squareMeters.toDouble() * 3.86102e-7);
}

QVariant FactMetaData::_squareMilesToSquareMeters(const QVariant& squareMiles)
{
    return QVariant(squareMiles.toDouble() * 258999039.98855);
}

QVariant FactMetaData::_metersPerSecondToMilesPerHour(const QVariant& metersPerSecond)
{
    return QVariant((metersPerSecond.toDouble() * 1.0/constants.milesToMeters) * constants.secondsPerHour);
}

QVariant FactMetaData::_milesPerHourToMetersPerSecond(const QVariant& milesPerHour)
{
    return QVariant((milesPerHour.toDouble() * constants.milesToMeters) / constants.secondsPerHour);
}

QVariant FactMetaData::_metersPerSecondToKilometersPerHour(const QVariant& metersPerSecond)
{
    return QVariant((metersPerSecond.toDouble() / 1000.0) * constants.secondsPerHour);
}

QVariant FactMetaData::_kilometersPerHourToMetersPerSecond(const QVariant& kilometersPerHour)
{
    return QVariant((kilometersPerHour.toDouble() * 1000.0) / constants.secondsPerHour);
}

QVariant FactMetaData::_metersPerSecondToKnots(const QVariant& metersPerSecond)
{
    return QVariant(metersPerSecond.toDouble() * constants.secondsPerHour / (1000.0 * constants.knotsToKPH));
}

QVariant FactMetaData::_knotsToMetersPerSecond(const QVariant& knots)
{
    return QVariant(knots.toDouble() * (1000.0 * constants.knotsToKPH / constants.secondsPerHour));
}

QVariant FactMetaData::_percentToNorm(const QVariant& percent)
{
    return QVariant(percent.toDouble() / 100.0);
}

QVariant FactMetaData::_normToPercent(const QVariant& normalized)
{
    return QVariant(normalized.toDouble() * 100.0);
}

QVariant FactMetaData::_centimetersToInches(const QVariant& centimeters)
{
    return QVariant(centimeters.toDouble() * 1.0/constants.inchesToCentimeters);
}

QVariant FactMetaData::_inchesToCentimeters(const QVariant& inches)
{
    return QVariant(inches.toDouble() * constants.inchesToCentimeters);
}

QVariant FactMetaData::_celsiusToFarenheit(const QVariant& celsius)
{
    return QVariant(celsius.toDouble() * (9.0 / 5.0) + 32);
}

QVariant FactMetaData::_farenheitToCelsius(const QVariant& farenheit)
{
    return QVariant((farenheit.toDouble() - 32) * (5.0 / 9.0));
}

QVariant FactMetaData::_kilogramsToGrams(const QVariant& kg) {
    return QVariant(kg.toDouble() * 1000);
}

QVariant FactMetaData::_ouncesToGrams(const QVariant& oz) {
    return QVariant(oz.toDouble() * constants.ouncesToGrams);
}

QVariant FactMetaData::_poundsToGrams(const QVariant& lbs) {
    return QVariant(lbs.toDouble() * constants.poundsToGrams);
}

QVariant FactMetaData::_gramsToKilograms(const QVariant& g) {
    return QVariant(g.toDouble() / 1000);
}

QVariant FactMetaData::_gramsToOunces(const QVariant& g) {
    return QVariant(g.toDouble() / constants.ouncesToGrams);
}

QVariant FactMetaData::_gramsToPunds(const QVariant& g) {
    return QVariant(g.toDouble() / constants.poundsToGrams);
}

void FactMetaData::setRawUnits(const QString& rawUnits)
{
    _rawUnits = rawUnits;
    _cookedUnits = rawUnits;

    setBuiltInTranslator();
}

FactMetaData::ValueType_t FactMetaData::stringToType(const QString& typeString, bool& unknownType)
{
    unknownType = false;

    for (size_t i=0; i<sizeof(_rgKnownTypeStrings)/sizeof(_rgKnownTypeStrings[0]); i++) {
        if (typeString.compare(_rgKnownTypeStrings[i], Qt::CaseInsensitive) == 0) {
            return _rgKnownValueTypes[i];
        }
    }

    unknownType = true;

    return valueTypeDouble;
}

QString FactMetaData::typeToString(ValueType_t type)
{
    for (size_t i=0; i<sizeof(_rgKnownTypeStrings)/sizeof(_rgKnownTypeStrings[0]); i++) {
        if (type == _rgKnownValueTypes[i]) {
            return _rgKnownTypeStrings[i];
        }
    }

    return QStringLiteral("UnknownType%1").arg(type);
}

size_t FactMetaData::typeToSize(ValueType_t type)
{
    switch (type) {
    case valueTypeUint8:
    case valueTypeInt8:
        return 1;

    case valueTypeUint16:
    case valueTypeInt16:
        return 2;

    case valueTypeUint32:
    case valueTypeInt32:
    case valueTypeFloat:
        return 4;

    case valueTypeUint64:
    case valueTypeInt64:
    case valueTypeDouble:
        return 8;

    case valueTypeCustom:
        return MAVLINK_MSG_PARAM_EXT_SET_FIELD_PARAM_VALUE_LEN;

    default:
        qWarning() << "Unsupported fact value type" << type;
        return 0;
    }
}

double FactMetaData::cookedIncrement(void) const
{
    return _rawTranslator(this->rawIncrement()).toDouble();
}

QVariant FactMetaData::cookedMax(void) const
{
    // We have to be careful with cooked min/max. Running the raw values through the translator could flip min and max.
    return qMax(_rawTranslator(_rawMax).toDouble(), _rawTranslator(_rawMin).toDouble());
}

QVariant FactMetaData::cookedMin(void) const
{
    // We have to be careful with cooked min/max. Running the raw values through the translator could flip min and max.
    return qMin(_rawTranslator(_rawMax).toDouble(), _rawTranslator(_rawMin).toDouble());
}

void FactMetaData::setVolatileValue(bool bValue)
{
    _volatile = bValue;
    if (_volatile) {
        _readOnly = true;
    }
}

int FactMetaData::decimalPlaces(void) const
{
    int actualDecimalPlaces = kDefaultDecimalPlaces;
    int incrementDecimalPlaces = kUnknownDecimalPlaces;

    // First determine decimal places from increment
    double increment = _rawTranslator(this->rawIncrement()).toDouble();
    if (!qIsNaN(increment)) {
        double integralPart;

        // Get the fractional part only
        increment = fabs(modf(increment, &integralPart));
        if (increment == 0.0) {
            // No fractional part, so no decimal places
            incrementDecimalPlaces = 0;
        } else {
            incrementDecimalPlaces = -ceil(log10(increment));
        }
    }

    if (_decimalPlaces == kUnknownDecimalPlaces) {
        if (incrementDecimalPlaces != kUnknownDecimalPlaces) {
            actualDecimalPlaces = incrementDecimalPlaces;
        } else {
            // Adjust decimal places for cooked translation
            int settingsDecimalPlaces = _decimalPlaces == kUnknownDecimalPlaces ? kDefaultDecimalPlaces : _decimalPlaces;
            double ctest = _rawTranslator(1.0).toDouble();

            settingsDecimalPlaces += -log10(ctest);

            settingsDecimalPlaces = qMin(25, settingsDecimalPlaces);
            settingsDecimalPlaces = qMax(0, settingsDecimalPlaces);
        }
    } else {
        actualDecimalPlaces = _decimalPlaces;
    }

    return actualDecimalPlaces;
}
