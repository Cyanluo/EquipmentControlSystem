#include "ECSApplication.h"
#include "GlobalQMLAcess.h"
#include "src/Fact/FactPanelController.h"
#include "src/ParameterManager/ParameterEditorController.h"

ECSApplication* ECSApplication::_app = nullptr;

static QObject* equitmentControlSystemQmlGlobalSingletonFactory(QQmlEngine*, QJSEngine*)
{
    GlobalQMLAcess* qmlGlobal = new GlobalQMLAcess(ecsApp(), ecsApp()->toolbox());
    qmlGlobal->setToolbox(ecsApp()->toolbox());

    return qmlGlobal;
}

ECSApplication::ECSApplication(int &argc, char* argv[])
    : QApplication(argc, argv)
{
    _app = this;
    _engine = new QQmlApplicationEngine;

    _toolbox = new ECSToolbox(this);
    _toolbox->setChildToolboxes();

    _vehicle = new Vehicle;

    ecsApp()->qmlEngine()->rootContext()->setContextProperty("activeVehicle", _vehicle);
    ecsApp()->qmlEngine()->rootContext()->setContextProperty("tbmPos", _vehicle->_tbmTrace);

    qmlRegisterSingletonType<GlobalQMLAcess>    ("EquitmentControl",                1, 0,   "EquitmentControl",         equitmentControlSystemQmlGlobalSingletonFactory);
    qmlRegisterType<ParameterEditorController>  ("EquitmentControl.Controllers",    1, 0,   "ParameterEditorController");
    qmlRegisterType<Fact>                       ("EquitmentControl.FactSystem",     1, 0,   "Fact");
    qmlRegisterType<FactMetaData>               ("EquitmentControl.FactSystem",     1, 0,   "FactMetaData");
    qmlRegisterType<FactPanelController>        ("EquitmentControl.FactSystem",     1, 0,   "FactPanelController");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(_engine, &QQmlApplicationEngine::objectCreated,
        this, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    _engine->load(url);

    QQuickWindow *window = qobject_cast<QQuickWindow *>(_engine->rootObjects().at(0));
    window->showMaximized();
}

ECSApplication::~ECSApplication()
{
    _app = nullptr;
    delete _engine;
    delete _vehicle;
    delete _toolbox;
}

ECSApplication* ecsApp(void)
{
    return ECSApplication::get_singleton();
}
