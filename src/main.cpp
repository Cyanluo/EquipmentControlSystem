#include <QGuiApplication>
//#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QQuickView>
#include "src/vehicle/TBM_Trace.h"
#include "src/MissionManager/polygons.h"
#include "src/vehicle/vehicle.h"
#include "src/MissionManager/missioncontroller.h"
#include "src/gcs_mavlink/NetworkUDP.h"

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
    Polygons::readMissionItem = missioncontroller.getMavMission();

    QObject::connect(&missioncontroller,&MissionController::readComplete,&polygons,&Polygons::convertToMissonitem);

    qmlRegisterType<Polygons>("Poj",1,0,"Polygons");
    qmlRegisterUncreatableType<Vehicle>("Object",1,0,"Vehicle","Reference only");
    qmlRegisterUncreatableType<MissionController>("Object",1,0,"MissionController","Reference only");
    qmlRegisterType<TBM_Trace>("setcoord",1,0,"SettingCoordinate");


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myPolygons",&polygons);
    engine.rootContext()->setContextProperty("activeVehicle",&vehicle);
    engine.rootContext()->setContextProperty("missioncontroller",&missioncontroller);
    engine.rootContext()->setContextProperty("myUdpNet",vehicle.my_mavlink->_mavprotocol->_udplink);
    engine.rootContext()->setContextProperty("tbmPos",vehicle._tbmTrace);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    //全屏显示
    if (engine.rootObjects().isEmpty())
        return -1;
    // 获取根窗口对象
    QQuickWindow *window = qobject_cast<QQuickWindow *>(engine.rootObjects().at(0));
    if (!window)
        return -2;
    // 设置窗口为全屏
    window->showMaximized();



    return app.exec();
}
