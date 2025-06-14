﻿#include <QGuiApplication>
#include "ECSApplication.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    ECSApplication app(argc, argv);

    return app.exec();
}
