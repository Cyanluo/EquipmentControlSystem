import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    anchors.fill: parent
    visible: true
    color: "white"

    property int status : 0

    function addPathPoint(p_x, p_y){
        var str_test = "import QtQuick 2.15;PathCurve {x:%1; y:%2}".arg(p_x).arg(p_y)

        var pathLine = Qt.createQmlObject(str_test, canvas)

        trace_path.pathElements.push(pathLine)
        trace_path.startX = trace_path.pathElements[0].x
        trace_path.startY = trace_path.pathElements[0].y

        canvas.requestPaint()
    }

    function deletePathPoint(reserve_num){
        trace_path.pathElements = Array.from(trace_path.pathElements).filter((m, i) => i >= trace_path.pathElements.length-reserve_num)

        if( trace_path.pathElements.length > 0 )
        {
            trace_path.startX = trace_path.pathElements[0].x
            trace_path.startY = trace_path.pathElements[0].y
        }

        canvas.requestPaint()
    }

    Path {
        id: trace_path
    }

    Canvas
    {
        id: canvas
        anchors.fill: parent
        smooth: true

        onPaint:
        {
            var context = canvas.getContext("2d")
            context.clearRect(0, 0, width, height)
            context.strokeStyle = "blue"
            context.lineWidth = 3
            context.path = trace_path
            context.stroke()

            context.fillStyle = "orange"
            context.beginPath()
            context.rect(trace_path.pathElements[trace_path.pathElements.length-1].x-10, trace_path.pathElements[trace_path.pathElements.length-1].y-10, 20, 20)
            context.fill()
        }
    }

    Button{
        id: reset_btn
        anchors.bottom: canvas.bottom
        anchors.right: status_btn.left
        anchors.bottomMargin: 20
        anchors.rightMargin: 10

        width:70
        height:30

        text: qsTr("清除")
        background: Rectangle{
            color: "white"
            anchors.fill: parent
            border.width: 1
            border.color: "black"
        }
        visible: status === 0

        onClicked: {
            deletePathPoint(1)
        }
    }

    TextField{
        id: disappeartime_text
        selectByMouse: true
        text: "600"
        font.pixelSize: 18
        Layout.preferredWidth: parent.width/2
        anchors.bottom: canvas.bottom
        anchors.right: status_btn.left
        anchors.bottomMargin: 20
        anchors.rightMargin: 10

        width:70
        height:30

        background: Rectangle{
            anchors.fill: parent
            color: "white"
            border.width: 1
            border.color: "black"
        }

        validator: RegExpValidator {
            regExp: /^-?\d+$/
        }

        visible: status === 1
    }

    Button{
        id: status_btn

        anchors.bottom: canvas.bottom
        anchors.right: canvas.right
        anchors.bottomMargin: 20
        anchors.rightMargin: 10

        width:100
        height:30

        background: Rectangle{
            color: "white"
            anchors.fill: parent
            border.width: 1
            border.color: "black"
        }
        text: {
            switch(status)
            {
            case 0:
                return qsTr("手动清除")
            case 1:
                return qsTr("自动清除")
            }
        }

        onClicked: {
            switch(status)
            {
            case 0:
                disappeartimer.running = true
                status = 1
                break;
            case 1:
                disappeartimer.running = false
                status = 0
                break;
            }
        }
    }

    Timer{
        id: disappeartimer
        interval: Number(disappeartime_text.text)
        repeat: true
        running: status === 1
        onTriggered: {
            deletePathPoint(12)
        }
    }

    Connections{
        target: tbmPos
        function onCoordinateChanged() {
            addPathPoint(tbmPos.coordinate_x, tbmPos.coordinate_y)
        }
    }
}
