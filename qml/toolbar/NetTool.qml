import QtQuick 2.15
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import EquitmentControl 1.0

Rectangle{
    property bool connectFlag: false
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    height: 120
    width: 80
    color: "transparent"

    ColumnLayout{
        id:bottonlayout

        anchors.fill: parent

        Button{
            id:disConnectButton
            text: connectFlag ? qsTr("关闭") : qsTr("连接")
            onClicked: {
                if(text === qsTr("关闭")) {
                    EquitmentControl.linkManager.close()
                    connectFlag = false
                }
                else {
                    EquitmentControl.linkManager.open()
                    connectFlag = true
                }
            }
        }
        Button{
            id:networkSettingBtn
            text: qsTr("网络设置")
            onClicked: {
                networkSettingDia.open()
            }
        }
    }

    Component{
        id: udpPage

        Rectangle{
            id: udpPageRec
            property alias  udpIpText: udpIpText.text
            property alias  updPortText: updPortText.text

            GridLayout{
                id: udpPageGridLayout
                columns: 2
                anchors.horizontalCenter: parent.horizontalCenter
                columnSpacing: 14
                rowSpacing: 14
                Text{
                    id: ip
                    text: qsTr("本地IP地址：")
                    font.pixelSize: 16
                }

                TextField{
                    id: udpIpText
                    selectByMouse: true
                    text: "127.0.0.1"
                    font.pixelSize: 18
                    Layout.preferredWidth: parent.width/2
                    background: Rectangle{
                        id:ipRec
                        anchors.fill: parent
                        color: "white"
                        border.width: 1
                        border.color: "black"
                    }
                }

                Text{
                    id: port
                    text: qsTr("本地端口号：")
                    font.pixelSize: 16
                }

                TextField{
                    id: updPortText
                    selectByMouse: true
                    text: "14551"
                    font.pixelSize: 18
                    Layout.preferredWidth: parent.width/2
                    background: Rectangle{
                        id:portRec
                        anchors.fill: parent
                        color: "white"
                        border.width: 1
                        border.color: "black"
                    }
                }
            }
        }
    }

    Component{
        id: serialPage

        Rectangle{
            id: serialPageRec
            property alias  serialPortText: serialPortText.text
            property alias  baudRateText: baudRateText.text

            GridLayout{
                id: serialPageGridLayout
                columns: 2
                anchors.horizontalCenter: parent.horizontalCenter
                columnSpacing: 14
                rowSpacing: 14
                Text{
                    id: serialPort
                    text: qsTr("串口名：")
                    font.pixelSize: 16
                }

                TextField{
                    id: serialPortText
                    selectByMouse: true
                    text: "/dev/pts/4"
                    font.pixelSize: 18
                    Layout.preferredWidth: parent.width/2
                    background: Rectangle{
                        id:ipRec
                        anchors.fill: parent
                        color: "white"
                        border.width: 1
                        border.color: "black"
                    }
                }

                Text{
                    id: baudRate
                    text: qsTr("波特率：")
                    font.pixelSize: 16
                }

                TextField{
                    id: baudRateText
                    selectByMouse: true
                    text: "115200"
                    font.pixelSize: 18
                    Layout.preferredWidth: parent.width/2
                    background: Rectangle{
                        id:portRec
                        anchors.fill: parent
                        color: "white"
                        border.width: 1
                        border.color: "black"
                    }
                }
            }
        }
    }

    Dialog {
        id: networkSettingDia
        title: qsTr("网络设置")

        onAccepted: {
            var linkType = netTypebox.textAt(netTypebox.currentIndex)
            EquitmentControl.linkManager.setIOType(linkType)

            if(linkType === "UDP") {
                EquitmentControl.linkManager.getConnectInfo(netSettingloader.item.udpIpText + "," + netSettingloader.item.updPortText)
            }
            else if(linkType === "Serial") {
                EquitmentControl.linkManager.getConnectInfo(netSettingloader.item.serialPortText + "," + netSettingloader.item.baudRateText)
            }
        }

        contentItem:  Rectangle{
            color: "white"
            implicitHeight : 220
            implicitWidth : 400

            ComboBox{
                id: netTypebox
                anchors.left: parent.left
                anchors.top: parent.top
                height: 50
                width: 140
                model: ListModel{
                        ListElement { text: "Serial" }
                        ListElement { text: "UDP" }
                }
                Component.onCompleted: {
                    EquitmentControl.linkManager.setIOType("UDP")
                    currentIndex = find(EquitmentControl.linkManager.ioType())
                    EquitmentControl.linkManager.getConnectInfo(netSettingloader.item.udpIpText + "," + netSettingloader.item.updPortText)
                }
            }

            Loader {
                id: netSettingloader
                anchors.top: netTypebox.bottom
                anchors.topMargin: 15
                anchors.right: parent.right
                anchors.bottom: netSettingBtns.bottom
                anchors.left: parent.left
                sourceComponent: {
                    if(netTypebox.currentText == "Serial") {
                        return serialPage
                    }
                    else if(netTypebox.currentText == "UDP") {
                        return udpPage
                    }
                }
            }

            RowLayout{
                id: netSettingBtns
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.right: parent.right
                width: 150
                height: 35

                Button{
                    text: qsTr("确定")
                    background: Rectangle{
                        color: "white"
                        height: 35
                        border.width: 1
                        border.color: "black"
                    }
                    onClicked: {
                        networkSettingDia.accepted()
                        networkSettingDia.close()
                    }
                }
                Button{
                    text: qsTr("取消")
                    background: Rectangle{
                        color: "white"
                        height: 35
                        border.width: 1
                        border.color: "black"
                    }
                    onClicked: {
                        networkSettingDia.rejected()
                        networkSettingDia.close()
                    }
                }
            }
        }
    }
}
