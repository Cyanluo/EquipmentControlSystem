import QtQuick 2.15
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Rectangle{
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    height: 120
    width: 340
    color: "transparent"

    ColumnLayout{
        id:namelayout
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width/4
        Text {
            id: ip
            text: qsTr("IP地址：")
            font.pixelSize: 18
        }
        Text {
            id: port
            text: qsTr("端口号：")
            font.pixelSize: 18
        }
    }
    ColumnLayout{
        id:textlayout
        anchors.left: namelayout.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width/2-30
        TextField{
            id:ipText
            selectByMouse: true
            text: "127.0.0.1"
            font.pixelSize: 18
            Layout.preferredWidth: textlayout.width
            background: Rectangle{
                id:ipRec
                anchors.fill: parent
                color: "white"
            }
        }
        TextField{
            id:portText
            selectByMouse: true
            text: "6666"
            font.pixelSize: 18
            Layout.preferredWidth: textlayout.width
            background: Rectangle{
                id:portRec
                anchors.fill: parent
                color: "white"
            }
        }
    }
    ColumnLayout{
        id:bottonlayout
        anchors.left: textlayout.right
        anchors.leftMargin: 25
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: parent.width/4
        Button{
            id:connectButton
            text: "连接"
            onClicked: {
                myUdpNet.getIpAndPort(ipText.text, portText.text)
            }
        }
        Button{
            id:disConnectButton
            text: "关闭"
            onClicked: {
                myUdpNet.udpClose()                                    //关闭udp
            }
        }
    }
    Connections{
        target: myUdpNet
        onUpdConnected:{
            ipText.readOnly = true
            portText.readOnly = true
            ipRec.color = "grey"
            portRec.color = "grey"
        }
        onUdpClosed:{
            ipText.readOnly = false
            portText.readOnly = false
            ipRec.color = "white"
            portRec.color = "white"
        }
    }
}
