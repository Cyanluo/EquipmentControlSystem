#ifndef MAVMISSION_H
#define MAVMISSION_H

#include <QObject>
#include "ardupilotmega/mavlink.h"

class MavMission : public QObject
{
    Q_OBJECT
public:
    explicit MavMission(QObject *parent = nullptr);


    void setCommand         (MAV_CMD command);
    void setSequenceNumber  (int sequenceNumber);
    void setFrame           (MAV_FRAME frame);
    void setAutoContinue    (bool autoContinue);
    void setParam1          (double param1);
    void setParam2          (double param2);
    void setParam3          (double param3);
    void setParam4          (double param4);
    void setParam5          (double param5);
    void setParam6          (double param6);
    void setParam7          (double param7);

    MAV_CMD         command         (void) const { return _command; }
    int             sequenceNumber  (void) const { return _sequenceNumber; }
    MAV_FRAME       frame           (void) const { return _frame; }
    bool            autoContinue    (void) const { return _autoContinue; }
    double          param1          (void) const { return _param1; }
    double          param2          (void) const { return _param2; }
    double          param3          (void) const { return _param3; }
    double          param4          (void) const { return _param4; }
    double          param5          (void) const { return _param5; }
    double          param6          (void) const { return _param6;}
    double          param7          (void) const { return _param7; }

private:
    MAV_CMD         _command;
    int             _sequenceNumber;
    MAV_FRAME       _frame;
    bool            _autoContinue;
    double          _param1;
    double          _param2;
    double          _param3;
    double          _param4;
    double          _param5;
    double          _param6;
    double          _param7;

signals:

};

#endif // MAVMISSION_H
