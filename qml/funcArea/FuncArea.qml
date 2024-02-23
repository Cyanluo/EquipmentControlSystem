import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import EquitmentControl     1.0

Rectangle {
    border.width: 1
    border.color: "black"

    TabBar {
        id: bar
        width: parent.width

        TabButton {
            width: 150
            text: qsTr("操作")
        }
        TabButton {
            width: 150
            text: qsTr("消息")
        }
        TabButton {
            width: 150
            text: qsTr("状态")
        }
        TabButton {
            width: 150
            text: qsTr("日志")
        }
    }

    StackLayout {
        width: parent.width
        currentIndex: bar.currentIndex
        anchors.top: bar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.right: parent.right
        Item {
            id: actionTab

            ScrollView{
                anchors.fill: parent
                GridLayout{
                    columns: 3
                    columnSpacing: 10
                    rowSpacing: 20

                    Button{
                        id:usart_test
                        width: 100
                        height: 80
                        property bool isSend : false
                        text: isSend ? qsTr('停止') : qsTr('记录')
                        onClicked: {
                            activeVehicle.saveMavToFile(!isSend)
                            isSend = !isSend
                        }
                    }
                    Button{
                        id:encipher_test1
                        width: 100
                        height: 80
                        text: qsTr('开启加密')
                        onClicked: {
                            activeVehicle.setVehicleEncipher(true)
                        }
                    }
                    Button{
                        id:encipher_test2
                        width: 100
                        height: 80
                        text: qsTr('关闭加密')
                        onClicked: {
                            activeVehicle.setVehicleEncipher(false)
                        }
                    }
                    Button{
                        id:encipher_test3
                        width: 140
                        height: 80
                        property bool isEncipher : EquitmentControl.linkManager.isGCSEncipher()
                        text:  isEncipher ? qsTr('地面站加密已开启') : qsTr('地面站加密已关闭')
                        onClicked: {
                            EquitmentControl.linkManager.setEncipher(!EquitmentControl.linkManager.isGCSEncipher())
                            isEncipher = EquitmentControl.linkManager.isGCSEncipher()
                        }
                    }
                }
            }
        }
        Item {
            id: messageTab
            Flickable {
                id: flick

                anchors.fill: parent
                contentWidth: edit.paintedWidth
                contentHeight: edit.paintedHeight
                clip: true

                function ensureVisible(r)
                {
                    if (contentX >= r.x)
                        contentX = r.x;
                    else if (contentX+width <= r.x+r.width)
                        contentX = r.x+r.width-width;
                    if (contentY >= r.y)
                        contentY = r.y;
                    else if (contentY+height <= r.y+r.height)
                        contentY = r.y+r.height-height;
                }

                 TextEdit {
                    id: edit
                    width: flick.width
                    focus: true
                    wrapMode: TextEdit.Wrap
                    onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
                }
            }

            Connections{
                target: activeVehicle
                function onReceiveMavMsg(msg) {
                    edit.append(qsTr(msg))
                }
            }
        }
        Item {
            id: statusTab
        }
        Item {
            id: logManageTab
        }
    }
}
