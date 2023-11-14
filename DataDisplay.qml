import QtQuick 2.15
import QtQuick.Controls 2.0

Rectangle {
    id: dataview
    border.width: 10
    border.color: "#483d8b"

    Rectangle{
        id:dataname
        anchors.left: dataview.left
        anchors.leftMargin: 12
        anchors.top: dataview.top
        anchors.topMargin: 12
        anchors.bottom: dataview.bottom
        anchors.bottomMargin: 12
        width: dataview.width/3-12
        color: "#87ceeb"

        Column{
            anchors.centerIn: dataname
            spacing: 50
            Label{
                width: dataview.width/3-12
                text: "飞控供电电压"
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
            }
            Label{
                width: dataview.width/3-12
                text: "油泵A相电流"
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
            }
            Label{
                width: dataview.width/3-12
                text: "温度"
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
            }
            Label{
                width: dataview.width/3-12
                text: "速度"
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
            }
        }

    }
    Rectangle{
        id:data
        anchors.left: dataname.right
        anchors.leftMargin: 6
        anchors.top: dataview.top
        anchors.topMargin: 12
        anchors.bottom: dataview.bottom
        anchors.bottomMargin: 12
        width: dataview.width/3
        color: "#87ceeb"
        Column{
            anchors.centerIn: data
            spacing: 15
            Rectangle{
                width: data.width-10
                height: 50
                border.width: 3
                border.color: "orange"
                Label{
                    id:volt
                    anchors.centerIn: parent
                    text: activeVehicle.powerVcc
                    font.pixelSize: 20
                }
            }
            Rectangle{
                width: data.width-10
                height: 50
                border.width: 3
                border.color: "orange"
                Label{
                    id: electricity
                    anchors.centerIn: parent
                    text: "0"
                    font.pixelSize: 20
                }
            }
            Rectangle{
                width: data.width-10
                height: 50
                border.width: 3
                border.color: "orange"
                Label{
                    id:temperature
                    anchors.centerIn: parent
                    text: "0"
                    font.pixelSize: 20
                }
            }
            Rectangle{
                width: data.width-10
                height: 50
                border.width: 3
                border.color: "orange"
                Label{
                    id:speed
                    anchors.centerIn: parent
                    text: "0"
                    font.pixelSize: 20
                }
            }
        }
    }
    Rectangle{
        id:units
        anchors.left: data.right
        anchors.leftMargin: 6
        anchors.top: dataview.top
        anchors.topMargin: 12
        anchors.bottom: dataview.bottom
        anchors.bottomMargin: 12
        width: dataview.width/3-24
        color: "#87ceeb"
        Column{
            anchors.centerIn: units
            spacing: 50
            Label{
                width:dataview.width/3-24
                horizontalAlignment: Text.AlignHCenter
                text: "mV"
                font.pixelSize: 20

            }
            Label{
                width:dataview.width/3-24
                horizontalAlignment: Text.AlignHCenter
                text: "A"
                font.pixelSize: 20

            }
            Label{
                width:dataview.width/3-24
                horizontalAlignment: Text.AlignHCenter
                text: "℃"
                font.pixelSize: 20

            }
            Label{
                width:dataview.width/3-24
                horizontalAlignment: Text.AlignHCenter
                text: "cm/s"
                font.pixelSize: 20

            }
        }
    }
}
