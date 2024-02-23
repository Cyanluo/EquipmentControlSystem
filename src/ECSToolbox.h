#ifndef ECSTOOLBOX_H
#define ECSTOOLBOX_H

#include <QObject>

class ECSApplication;
class Polygons;
class Vehicle;
class MissionController;
class GCS_Mavlink;

class ECSToolbox : public QObject
{
    Q_OBJECT

public:
    explicit ECSToolbox(ECSApplication *app = nullptr);

    ~ECSToolbox();

    GCS_Mavlink* linkManager() { return _linkManager; }
    MissionController* missionController() { return _missionController; }

private:
    void setChildToolboxes(void);

    GCS_Mavlink*    _linkManager;
    MissionController* _missionController;

    friend class ECSApplication;
};

class ECSTool : public QObject
{
    Q_OBJECT

public:
    ECSTool(ECSApplication* app, ECSToolbox* toolbox);

    virtual void setToolbox(ECSToolbox* toolbox);

protected:
    ECSApplication* _app;
    ECSToolbox*     _toolbox;
};

#endif // ECSTOOLBOX_H
