import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls 2.0
import QtQuick.Controls 2.15

import setcd 1.0

Window {
    id:mainwindow
    width: Screen.desktopAvailableWidth-15
    height: Screen.desktopAvailableHeight-40
    visible: true


    Item {
        id: mainitem
        anchors.fill: parent
        Rectangle{
            id:topbar
            anchors.left: mainitem.left
            anchors.top: mainitem.top
            anchors.right: mainitem.right
            height: 120
            color: "black"


            Canvas{
                id:leftTop
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.lineWidth = 1
                    ctx.fillStyle = "#4682b4"
                    ctx.beginPath()
                    ctx.moveTo(0,0)
                    ctx.lineTo(0,120)
                    ctx.lineTo(mainitem.width*2/7,120)
                    ctx.lineTo(mainitem.width*2/7-250,0)
                    ctx.closePath()
                    ctx.fill()

                    var ctx1 = getContext("2d")
                    ctx1.lineWidth = 1
                    ctx1.fillStyle = "#4682b4"
                    ctx1.beginPath()
                    ctx1.moveTo(mainitem.width,0)
                    ctx1.lineTo(mainitem.width,120)
                    ctx1.lineTo(mainitem.width*5/7,120)
                    ctx1.lineTo(mainitem.width*5/7+250,0)
                    ctx1.closePath()
                    ctx1.fill()

                    var ctx2 = getContext("2d")
                    ctx2.lineWidth = 1
                    ctx2.fillStyle = "#191970"
                    ctx2.beginPath()
                    ctx2.moveTo(mainitem.width*2/7-230, 0)
                    ctx2.lineTo(mainitem.width*2/7+20, 120)
                    ctx2.lineTo(mainitem.width*5/7-20, 120)
                    ctx2.lineTo(mainitem.width*5/7+230, 0)
                    ctx2.closePath()
                    ctx2.fill()
                }
            }

            Label{
                anchors.centerIn: parent
                text: "掘进机远程控制系统"
                font.pixelSize: 50
                color: "white"
            }


        }

        ConnectState{
            id:connectDisplay
            anchors.top: topbar.bottom
            anchors.right: parent.right
            anchors.bottom: datadisplay.top
            anchors.left: parent.left
        }

        DataDisplay{
            id:datadisplay
            anchors.top: topbar.bottom
            anchors.topMargin: 15
            anchors.bottom: mainitem.bottom
            anchors.left: mainitem.left
            width: mainitem.width*2/9
        }
        PlanView{
            id:planview
            anchors.top: topbar.bottom
            anchors.topMargin: 15
            anchors.bottom: mainitem.bottom
            anchors.bottomMargin: 300
            anchors.left: datadisplay.right
            width: mainitem.width*5/9
        }
        YawDisplay{
            id:yawdisplay
            anchors.top: topbar.bottom
            anchors.topMargin: 15
            anchors.bottom: mainitem.bottom
            anchors.left: planview.right
            width: mainitem.width*2/9
        }
        Pitch_A_Roll{
            anchors.top: planview.bottom
            anchors.bottom: mainitem.bottom
            anchors.left: datadisplay.right
            anchors.right: yawdisplay.left
        }
//        Button{
//            id:usart_test
//            width: 100
//            height: 60
//            anchors.left: datadisplay.left
//            anchors.top: datadisplay.top
//            text: "send"
//            onClicked: {
//                myPolygons.senddata()
//            }
//        }
    }
}
