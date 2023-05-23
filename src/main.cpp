#include <QGuiApplication>
//#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "drawtrace.h"
#include "src/MissionManager/polygons.h"
#include "src/vehicle/vehicle.h"
#include "src/MissionManager/missioncontroller.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    Polygons polygons;
    Vehicle vehicle;
    MissionController missioncontroller(&vehicle);


    MissionController::missionlist = polygons.polygons();


    qmlRegisterUncreatableType<Polygons>("Object",1,0,"Polygons","Reference only");
    qmlRegisterUncreatableType<Vehicle>("Object",1,0,"Vehicle","Reference only");
    qmlRegisterUncreatableType<MissionController>("Object",1,0,"MissionController","Reference only");
    qmlRegisterType<DrawTrace>("setcd",1,0,"SettingCoordinate");


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myPolygons",&polygons);
    engine.rootContext()->setContextProperty("activeVehicle",&vehicle);
    engine.rootContext()->setContextProperty("missioncontroller",&missioncontroller);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
