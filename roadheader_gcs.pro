 QT += quick \
    widgets
 QT += network
 QT += serialport
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/libs/mavlink/include/v2.0

SOURCES += \
        src/MissionManager/mavmission.cpp \
        src/MissionManager/missioncontroller.cpp \
        src/MissionManager/missionitem.cpp \
        src/MissionManager/planmanager.cpp \
        src/MissionManager/polygons.cpp \
        src/MissionManager/qmlobjectlistmodel.cpp \
        src/drawtrace.cpp \
        src/gcs_mavlink/MAVLinkProtocol.cpp \
        src/gcs_mavlink/gcs_mavlink.cpp \
        src/gcs_mavlink/seriallink.cpp \
        src/main.cpp \
        src/mainwindow.cpp \
        src/vehicle/vehicle.cpp

RESOURCES += qml.qrc \
    yawimage.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/MissionManager/mavmission.h \
    src/MissionManager/missioncontroller.h \
    src/MissionManager/missionitem.h \
    src/MissionManager/planmanager.h \
    src/MissionManager/polygons.h \
    src/MissionManager/qmlobjectlistmodel.h \
    src/drawtrace.h \
    src/gcs_mavlink/MAVLinkProtocol.h \
    src/gcs_mavlink/gcs_mavlink.h \
    src/gcs_mavlink/seriallink.h \
    src/mainwindow.h \
    src/vehicle/vehicle.h

DISTFILES +=
