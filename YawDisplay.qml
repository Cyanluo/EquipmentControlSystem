import QtQuick 2.15
import QtQuick.Controls 2.0

Rectangle {
    id:yawdisplay
    width:200
    border.width: 10
    border.color: "#483d8b"
    property real leftdistance: 1000
    property real rightdistance: 1000
    property real angleOffset:activeVehicle.yawOffset*57.3
    property real rotangle: activeVehicle.yaw*57.3 -angleOffset
    property bool isadd: true


    //标题绘制
    Rectangle{
        id:titleRec
        anchors.top: parent.top
        //anchors.topMargin: 10
        anchors.left: parent.left
        //anchors.leftMargin: 10
        anchors.right: parent.right
        //anchors.rightMargin: 10
        height: 60
        border.color: "#483d8b"
        border.width: 8
        Label{
            anchors.centerIn: parent
            text: "偏航显示"
            font.pixelSize: 30
        }
    }
    //数据显示部分
    Rectangle{
        id:yawdata
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        height: 159
        Column{
            id:dataname
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 60
            anchors.top: parent.top
            anchors.topMargin: 20
            width: yawdata.width/2
            spacing: 3
            Label{
                width:yawdata.width/2
                height: 50
                horizontalAlignment: Text.AlignHCenter
                anchors.left: parent.left
                anchors.right: parent.right
                text: "机身偏向角:"
                font.pixelSize: 20
            }
            Label{
                width:yawdata.width/2
                height: 50
                horizontalAlignment: Text.AlignHCenter
                anchors.left: parent.left
                anchors.right: parent.right
                text: "左巷距:"
                font.pixelSize: 20
            }
            Label{
                width:yawdata.width/2
                height: 50
                horizontalAlignment: Text.AlignHCenter
                anchors.left: parent.left
                anchors.right: parent.right
                text: "右巷距:"
                font.pixelSize: 20
            }

        }
        Column{
            id:data
            anchors.bottom: parent.bottom
            anchors.left: dataname.right
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.topMargin: 20
            spacing: 20
            Rectangle{
                anchors.left: data.left
                anchors.right: data.right
                height: 30
                border.width: 2
                border.color: "orange"
                Label {
                    anchors.centerIn: parent
                    text: rotangle>0? "右偏"+rotangle.toFixed(2) + "°":"左偏"+(-rotangle).toFixed(2)+"°"
                    font.pixelSize: 20
                }
            }
            Rectangle{
                anchors.left: data.left
                anchors.right: data.right
                height: 30
                border.width: 2
                border.color: "orange"
                Label{
                    anchors.centerIn: parent
                    text: leftdistance + "mm"
                    font.pixelSize: 20
                }
            }
            Rectangle{
                anchors.left: data.left
                anchors.right: data.right
                height: 30
                border.width: 2
                border.color: "orange"
                Label{
                    anchors.centerIn: parent
                    text: rightdistance + "mm"
                    font.pixelSize: 20
                }
            }
        }
    }

    //虚线绘制
    Rectangle{
        id: displayrec
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.bottom: yawdata.top
        anchors.bottomMargin: 5
        anchors.top: titleRec.bottom
        border.width: 2
        border.color: "#483d8b"
        Column{
            width:1
            spacing: 5
            clip: true
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            Repeater{
                anchors.fill: parent
                anchors.bottomMargin: 10
                model: 40
                delegate:Rectangle{
                    width: 1
                    height: 10
                    color: "black"
                }
            }
        }
        Column{
            width:1
            spacing: 5
            clip: true
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            Repeater{
                anchors.fill: parent
                model: 40
                delegate:Rectangle{
                    width:1
                    height: 10
                    color: "black"
                }
            }
        }

        Row{
            width: parent.width
            height: 1
            spacing: 5
            clip: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            Repeater{
                anchors.fill: parent
                model: 28
                delegate:Rectangle{
                    width: 10
                    height: 1
                    color: "black"
                }
            }
        }

        Column{
            width:1
            height:parent.height
            spacing: 8
            clip: true
            anchors.centerIn: parent
            Repeater{
                anchors.fill: parent
                model: 33
                delegate:Rectangle{
                    width:1
                    height: 10
                    color: "black"
                }
            }
        }
    }
    Rectangle{
        x:parent.width/2-100
        width: 200
        height: 300
        anchors.bottom: yawdata.top
        anchors.bottomMargin: 40
        Image {
            anchors.fill: parent
            id: yawimage
            source: "qrc:/new/prefix1/image/yawimage.png"
            rotation: rotangle
        }
    }
//    Timer {
//            id: timer;
//            interval: 100;
//            repeat: true
//            running: true
//            triggeredOnStart: false
//            onTriggered: {
//                changeangle()
//                //console.log(rotangle)
//            }
//    }
}
