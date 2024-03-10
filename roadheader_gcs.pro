 QT += quick \
    widgets
 QT += network
 QT += serialport
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/libs/mavlink/include/v2.0 \
                $$PWD/libs/tinycrypt/include

SOURCES += \
        libs/tinycrypt/src/aes_decrypt.c \
        libs/tinycrypt/src/aes_encrypt.c \
        libs/tinycrypt/src/cbc_mode.c \
        libs/tinycrypt/src/utils.c \
        src/ECSApplication.cpp \
        src/ECSToolbox.cpp \
        src/Encipher/AESAssembler.cpp \
        src/Encipher/AESEncipher.cpp \
        src/Fact/Fact.cpp \
        src/Fact/FactMetaData.cpp \
        src/GlobalQMLAcess.cpp \
        src/MissionManager/mavmission.cpp \
        src/MissionManager/missioncontroller.cpp \
        src/MissionManager/missionitem.cpp \
        src/MissionManager/planmanager.cpp \
        src/MissionManager/polygons.cpp \
        src/MissionManager/qmlobjectlistmodel.cpp \
        src/ParameterManager/APMParameterMetaData.cpp \
        src/ParameterManager/ParameterManager.cpp \
        src/gcs_mavlink/MAVLinkProtocol.cpp \
        src/gcs_mavlink/NetworkUDP.cpp \
        src/gcs_mavlink/gcs_mavlink.cpp \
        src/gcs_mavlink/seriallink.cpp \
        src/main.cpp \
        src/vehicle/InitialConnectStateMachine.cpp \
        src/vehicle/StateMachine.cpp \
        src/vehicle/TBM_Trace.cpp \
        src/vehicle/vehicle.cpp

RESOURCES += qml.qrc \
    doc/doc.qrc \
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
    src/ECSApplication.h \
    src/ECSToolbox.h \
    src/Encipher/AESEncipher.h \
    src/Encipher/queue.h \
    src/Encipher/staticqueue.h \
    src/Fact/Fact.h \
    src/Fact/FactMetaData.h \
    src/GlobalQMLAcess.h \
    src/MissionManager/mavmission.h \
    src/MissionManager/missioncontroller.h \
    src/MissionManager/missionitem.h \
    src/MissionManager/planmanager.h \
    src/MissionManager/polygons.h \
    src/MissionManager/qmlobjectlistmodel.h \
    src/ParameterManager/APMParameterMetaData.h \
    src/ParameterManager/ParameterManager.h \
    src/gcs_mavlink/AbstractIO.h \
    src/gcs_mavlink/MAVLinkProtocol.h \
    src/gcs_mavlink/NetworkUDP.h \
    src/gcs_mavlink/gcs_mavlink.h \
    src/gcs_mavlink/seriallink.h \
    src/vehicle/InitialConnectStateMachine.h \
    src/vehicle/StateMachine.h \
    src/vehicle/TBM_Trace.h \
    src/vehicle/vehicle.h

DISTFILES +=
