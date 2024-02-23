#ifndef ECSAPPLICATION_H
#define ECSAPPLICATION_H

#include <QObject>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QQuickView>
#include "src/vehicle/vehicle.h"
#include "src/ECSToolbox.h"

class ECSApplication : public QApplication
{
    Q_OBJECT
public:
    explicit ECSApplication(int &argc, char* argv[]);
    virtual ~ECSApplication() override;

    ECSToolbox* toolbox() { return _toolbox; }
    QQmlApplicationEngine* qmlEngine() { return _engine; }
    Vehicle* activeVehicle() { return _vehicle; }

    // get singleton instance
    static ECSApplication *get_singleton()
    {
        return _app;
    }

private:
    static ECSApplication*  _app;

    QQmlApplicationEngine* _engine;

    ECSToolbox* _toolbox;
    Vehicle* _vehicle;
};

ECSApplication* ecsApp(void);

#endif // ECSAPPLICATION_H
