#include <QGuiApplication>
//#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QQuickView>
#include "drawtrace.h"
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
    NetworkUDP myUdpNet;


    MissionController::missionlist = polygons.polygons();
    Polygons::readMissionItem = missioncontroller.getMavMission();

    QObject::connect(&missioncontroller,&MissionController::readComplete,&polygons,&Polygons::convertToMissonitem);

    qmlRegisterType<Polygons>("Poj",1,0,"Polygons");
    qmlRegisterUncreatableType<Vehicle>("Object",1,0,"Vehicle","Reference only");
    qmlRegisterUncreatableType<MissionController>("Object",1,0,"MissionController","Reference only");
    qmlRegisterType<DrawTrace>("setcd",1,0,"SettingCoordinate");
    qmlRegisterUncreatableType<NetworkUDP>("Udp",1,0,"NetworkUDP","Reference only");


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myPolygons",&polygons);
    engine.rootContext()->setContextProperty("activeVehicle",&vehicle);
    engine.rootContext()->setContextProperty("missioncontroller",&missioncontroller);
    engine.rootContext()->setContextProperty("myUdpNet",&myUdpNet);
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

//    QQuickView view;
//    view.setResizeMode(QQuickView::SizeRootObjectToView);
//    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));

//    QObject::connect(view.engine(), &QQmlEngine::quit, &app, &QGuiApplication::quit);

//    // 监听窗口大小变化事件
//    QObject::connect(view.engine(), &QQmlEngine::quit, &app, &QGuiApplication::quit);

//    QObject::connect(&view, &QQuickView::widthChanged, [&view]() {
//        // 屏幕宽度变化时刷新显示
//        view.update();
//    });

//    QObject::connect(&view, &QQuickView::heightChanged, [&view]() {
//        // 屏幕高度变化时刷新显示
//        view.update();
//    });

    return app.exec();
}
