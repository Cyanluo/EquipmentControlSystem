import QtQuick 2.15
import QtGraphicalEffects 1.13
//连接状态显示
Rectangle{
    id:mainRec
    property real progress:              0
    property bool isTimerWork:           activeVehicle.beginConnect
    property bool isConnectedRecVisable: activeVehicle.isConnected
    property bool isProgressRecVisable:  activeVehicle.beginConnect
    property bool isProgressDone:        false

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
                //GradientStop { position: 1.0; color: "green" }
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
        width: progress
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
                //GradientStop { position: 1.0; color: "green" }
            }
        }
        Text {
            id: connected
            text: qsTr("Connected")
        }
    }



    Timer {
        id: timer
        interval: 10
        repeat: true
        running: isTimerWork
        triggeredOnStart: false
        onTriggered: {
            if(progress <=parent.width){
                progress = progress + 20;
            }
            else{
                isProgressDone = true;
            }

            if(isConnectedRecVisable){
                progress = 0;
            }
        }
    }
}
