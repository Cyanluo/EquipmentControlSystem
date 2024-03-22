import QtQuick 2.15

Rectangle {
    id:pitch_a_roll
    property real rollangle: activeVehicle.roll*57.3
    property real pitchangle: activeVehicle.pitch*57.3
    property bool isaddR:  true
    property bool isaddP:  true

    Row{
        anchors.fill: parent
        Rectangle{
            id:picthA
            width:parent.width/2
            height: parent.height
            color: "#191970"
            Rectangle{
                anchors.fill: parent
                anchors.rightMargin: 5
                anchors.topMargin: 5
                anchors.bottomMargin: 10
                //虚线
                Row{
                    width:1
                    spacing: 5
                    clip: true
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.right: parent.right
                    anchors.rightMargin: 15
                    y:parent.height/2
                    Repeater{
                        anchors.fill: parent
                        anchors.bottomMargin: 10
                        model: 40
                        delegate:Rectangle{
                            width: 10
                            height: 1
                            color: "black"
                        }
                    }
                }
                Text {
                    id: picthtitle
                    text: qsTr("俯仰角:")
                    font.pixelSize: 20
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.leftMargin: 10
                    anchors.topMargin: 10
                }
                Rectangle{
                    anchors.left: picthtitle.right
                    anchors.leftMargin: 10
                    anchors.top: parent.top
                    anchors.topMargin: 4
                    width: picthtitle.width +18
                    height: picthtitle.height+13
                    border.width: 2
                    border.color: "orange"
                    Text {
                        anchors.centerIn: parent
                        id: pitchdata
                        text: pitchangle.toFixed(2) + "°"
                        font.pixelSize: 20
                    }
                }
                Rectangle{
                    //x:parent.width/2-150
                    width: 400
                    height: 200
                    anchors.centerIn: parent
                    Image {
                        anchors.fill: parent
                        id: pitchimage
                        source: "qrc:/new/prefix1/image/lateralView.png"
                        rotation: pitchangle
                    }
                }
            }
        }
        Rectangle{
            id:rollA
            width:parent.width/2
            height: parent.height
            color: "#191970"
            Rectangle{
                anchors.fill: parent
                anchors.leftMargin: 5
                anchors.topMargin: 5
                anchors.bottomMargin: 10
                Text {
                    id: rolltitel
                    text: qsTr("滚转角:")
                    font.pixelSize: 20
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.leftMargin: 10
                    anchors.topMargin: 10
                }
                Rectangle{
                    id:imageRec
                    x:parent.width/2-125
                    width: 250
                    height: 160
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 50
                    Image {
                        anchors.fill: imageRec
                        id: rollimage
                        source: "qrc:/new/prefix1/image/Roll.png"
                        transform:Rotation {origin.x:imageRec.width/2;origin.y:imageRec.width/2; axis { x: 0; y: 0; z: 1 } angle: rollangle }
                    }
                }
                Rectangle{
                    anchors.left: rolltitel.right
                    anchors.leftMargin: 10
                    anchors.top: parent.top
                    anchors.topMargin: 4
                    width: rolltitel.width +18
                    height: rolltitel.height+13
                    border.width: 2
                    border.color: "orange"
                    Text {
                        anchors.centerIn: parent
                        id: rolldata
                        text: rollangle.toFixed(2) + "°"
                        font.pixelSize: 20
                    }
                }
            }
        }
    }
}
