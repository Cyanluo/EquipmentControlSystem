import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Window 2.0
import "./qml/traceDisplay/"

Rectangle {
    id: midview
    property bool showplan: true
    property real index: 0
    property bool exist_a_user_path: false
    property bool exist_a_path: false
    property bool afterReadWP: false


    Rectangle{
        id:planview
        anchors.fill: parent
        visible: showplan
        border.width: 4
        border.color: "#191970"
        z:4
        color:"black"

        Row{
            width: parent.width
            height: 1
            spacing: 5
            clip: true
            anchors.top: parent.top
            anchors.topMargin: parent.height/2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            Repeater{
                anchors.fill: parent
                model: 100
                delegate:Rectangle{
                    width: 10
                    height: 1
                    color: "#2b5876"
                }
            }
        }

        Column{
            width:1
            spacing: 5
            clip: true
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: parent.width/4
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            Repeater{
                anchors.fill: parent
                model: 75
                delegate:Rectangle{
                    width:1
                    height: 10
                    color: "#2b5876"
                }
            }
        }

        Column{
            width:1
            spacing: 5
            clip: true
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: parent.width*3/4
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            Repeater{
                anchors.fill: parent
                model: 75
                delegate:Rectangle{
                    width:1
                    height: 10
                    color: "#2b5876"
                }
            }
        }

        Column{
            width:1
            spacing: 5
            clip: true
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: parent.width/2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            Repeater{
                anchors.fill: parent
                model: 75
                delegate:Rectangle{
                    width:1
                    height: 10
                    color: "#2b5876"
                }
            }
        }

        Rectangle{
            width: 2
            height: 2
            radius: 1
            x: 861
            y: 222
            color: "red"
        }

        Rectangle{
            width: 2
            height: 2
            radius: 1
            x: 790
            y: 505
            color: "red"
        }

        Rectangle{
            width: 2
            height: 2
            radius: 1
            x: 582
            y: 547
            color: "red"
        }

        Rectangle{
            width: 2
            height: 2
            radius: 1
            x: 318.5
            y: 361
            color: "red"
        }

        Rectangle{
            width: 2
            height: 2
            radius: 1
            x: 298.5
            y: 258
            color: "red"
        }



        function addindex(){
            index = index + 1
        }



        MouseArea{
            anchors.fill: parent
            onClicked: {
                if(afterReadWP)
                {
                    //读当前的航点index
                    index = myPolygons.getNowIndex()
                    afterReadWP = false
                }
                planview.addindex()
                myPolygons.getPlanScreenWH(midview.width,midview.height)
                myPolygons.setIndex(index)
                myPolygons.setGetx(mouseX)
                myPolygons.setGety(mouseY)
                myPolygons.setprecoordinate(mouseX,mouseY)
                console.log(mouseX,mouseY)
                exist_a_path = true
                if(!myPolygons.getisInsert())
                    myPolygons.setMissionitemfocus(index)

                console.log(midview.width,midview.height)
            }
        }

        Repeater{
            model: myPolygons.polygons
            delegate:MissionItemIndexLabel{
                z:4
                labelx: model.object.number_x
                labely: model.object.number_y
                index: model.object.missionindex
                checked: model.object.focus
                onClicked: {
                    myPolygons.setMissionitemfocus(index)
                }
            }
        }

        Repeater{
            model:myPolygons.lineModel
            delegate: PloyLine{
                z:3
                currentx:  model.object.number_x
                currenty:  model.object.number_y
                previousx: model.object.prenumber_x
                previousy: model.object.prenumber_y
                count: index
            }
        }

//        Button{
//            id:networkTest
//            anchors.top: planview.top
//            anchors.left: planview.left
//            text: "网络测试"
//            onClicked: {//调用udp发送函数，发一段数字
//                console.log("UDP Test")
//                myUdpNet.udpSendData()
//            }
//        }

        Button{
            id:uplaodbutton
            anchors.bottom: planview.bottom
            anchors.right: planview.right
            text: "写入航点"
            onClicked: uplaoddialog.open()
        }
        Button{
            id:readbutton
            anchors.bottom: planview.bottom
            anchors.right: uplaodbutton.left
            anchors.rightMargin: 2
            text: "读取航点"
            onClicked: readdialog.open()
        }
        Rectangle{
            id:clearbutton
            anchors.bottom: planview.bottom
            anchors.left: planview.left
            width: 80
            height: 42
            color: "black"
            Button{
                anchors.fill: parent
                anchors.leftMargin: 2
                text: "清除航点"
                onClicked: {
                    myPolygons.clearmissionlist()
                    exist_a_path = false
                    exist_a_user_path = false
                    index = 0
                }
            }
        }
        Rectangle{
            id:userpathbutton
            anchors.bottom: planview.bottom
            anchors.left: clearbutton.right
            width: 120
            height: 42
            color: "black"
            Button{
                anchors.fill: parent
                anchors.leftMargin: 2
                text: "自定义路径1"
                onClicked: {
                    if(!exist_a_user_path&&!exist_a_path)
                    {
                        myPolygons.getPlanScreenWH(midview.width,midview.height)
                        myPolygons.userDefineMissionSimple()
                        index = 12
                        exist_a_user_path = true
                        exist_a_path = true
                    }
                    else if(exist_a_user_path)
                    {
                        userpathdialog.open()
                    }
                    else {
                        userpathdialog1.open()
                    }
                }
            }
        }
        Rectangle{
            anchors.left: userpathbutton.right
            anchors.bottom: planview.bottom
            width: 130
            height: 42
            color: "black"
            Button{
                id:deletemission
                anchors.fill: parent
                anchors.leftMargin: 2
                text: "删除当前任务点"
                onClicked: {
                    if(!exist_a_path&&!exist_a_user_path){
                        delmissiondia.open()
                    }
                    else{
                        myPolygons.missiondel()
                        index = index - 1
                    }
                    if(index == 0){
                        exist_a_path = false
                    }

                }
            }
        }
    }

//    TraceDisplay{
//        id:traceview
//        visible: !showplan
//        border.width: 4
//        border.color: "#483d8b"
//    }

    TraceDisplayPro{
        id:traceviewpro
        visible: !showplan
        border.width: 4
        border.color: "#483d8b"
    }

    Button {
        id:traceButton
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.rightMargin: 10
        background:Rectangle{
            anchors.fill: parent
            color: !showplan? "#a3bded":"#eef1f5"
        }
        width: 100
        height: 45
        text: "截割轨迹"
        font.pixelSize: 18
        z:4

        onClicked: {
            showplan = false
        }
    }

    Button {
        id:planButton
        anchors.right: traceButton.left
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.rightMargin: 5
        background:Rectangle{
            anchors.fill: parent
            color: showplan? "#a3bded":"#eef1f5"
        }
        width: 100
        height: 45
        text: "航点规划"
        font.pixelSize: 18
        z:4

        onClicked: {
            showplan = true
        }
    }

    Dialog {
        id: uplaoddialog
        anchors.centerIn: parent
        title: "Do you want to upload routedata?"
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted:
        {
            missioncontroller.sendToVehicle()
            console.log("Ok clicked")
        }
        onRejected: console.log("Cancel clicked")
    }
    Dialog {
        id: readdialog
        anchors.centerIn: parent
        title: "Do you want to read from vehicle?"
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted:
        {
            exist_a_path = true
            myPolygons.getPlanScreenWH(midview.width,midview.height);
            missioncontroller.loadFromVehicle()
            afterReadWP = true
            console.log("Ok clicked")
        }
        onRejected: console.log("Cancel clicked")
    }
    Dialog {
        id: userpathdialog
        anchors.centerIn: parent
        title: "提示"
        standardButtons: Dialog.Ok | Dialog.Cancel
        modal: true
        Label{
            text: "已经有一个自定义路径了，是否重新打开一个自定义路径"
        }
        onAccepted: {
            myPolygons.clearmissionlist()
            myPolygons.userDefineMissionSimple()
            index = 12
        }
        onRejected: console.log("Cancel clicked")
    }
    Dialog {
        id: userpathdialog1
        anchors.centerIn: parent
        title: "提示"
        standardButtons: Dialog.Ok | Dialog.Cancel
        modal: true
        Label{
            text: "是否保留原来的编辑"
        }
        onAccepted: console.log("ok clicked")
        onRejected: {
            myPolygons.clearmissionlist()
            myPolygons.userDefineMissionSimple()
            index = 12
        }
    }
    Dialog{
        id:delmissiondia
        anchors.centerIn: parent
        title: "提示"
        modal: true
        Label{
            text: "无可删除任务点"
        }
        standardButtons: Dialog.Ok
        onAccepted: console.log("ok clicked")
    }
}
