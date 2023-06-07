import QtQuick 2.15
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Rectangle{
    id:root
    width: 380
    height: 100
    color: "transparent"
    property bool isConnect: myUdpNet.udpConnect
    GridLayout{
        anchors.fill: parent
        columns:3
        Text{
            id: ip
            font.pixelSize: 18
            text: qsTr("IP地址：")
        }
        TextField{
            id:iptext
            selectByMouse: true
        }
        Button{
            id:connect
            text: "连接"
            highlighted: isConnect
            onClicked: {
                myUdpNet.getIpAndPort(iptext.text, porttext.text)
                console.log(isConnect)
                console.log(myUdpNet.udpConnect)
            }
        }
        Text{
            id: port
            font.pixelSize: 18
            text: qsTr("端口号：")
        }
        TextField{
            id:porttext
            selectByMouse: true
        }
        Button{
            id:disconnect
            text: "断开"
        }
    }
}
