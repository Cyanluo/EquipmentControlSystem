import QtQuick 2.15
import QtGraphicalEffects 1.13
//连接状态显示
Rectangle{
    id:mainRec
    property bool isConnectedRecVisable: activeVehicle.isConnected
    property bool isProgressRecVisable:  activeVehicle.beginConnect
    property real progress:              0

    Rectangle{
        id:disconnectedRec
        anchors.fill: parent
        LinearGradient{
            anchors.fill: parent
            start: Qt.point(0, 0)
            end:Qt.point(parent.width, 0)
            gradient: Gradient{
                GradientStop { position: 0.0; color: "purple" }
                GradientStop { position: 0.33; color: "gray" }
            }
        }
        Text {
            id: disconnect
            text: qsTr("Disconnected")
        }
    }

    //进度条
    Rectangle{
        id:progressRec
        visible: isProgressRecVisable
        height: parent.height
        width:  progress
        color: "#9be15d"
    }

    Rectangle{
        id:connectedRec
        anchors.fill: parent
        visible: isConnectedRecVisable
        LinearGradient{
            anchors.fill: parent
            start: Qt.point(0, 0)
            end:Qt.point(parent.width, 0)
            gradient: Gradient{
                GradientStop { position: 0.0; color: "#96fbc4" }
                GradientStop { position: 0.33; color: "#f9f586" }
            }
        }
        Text {
            id: connected
            text: qsTr("Connected")
        }
    }

    Timer {
        id: timer
        interval: 200
        repeat: true
        running: isProgressRecVisable
        triggeredOnStart: false
        onTriggered: {
            progress = parent.width * activeVehicle.progress
        }
    }
}
