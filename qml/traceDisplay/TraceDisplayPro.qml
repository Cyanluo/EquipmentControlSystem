import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.4

import setcoord 1.0

Rectangle {
    id: root
    anchors.fill: parent
    visible: true
    color: "white"

    property var rdHeaderTrace:         [ ]
    property var rdhdconnecttrace:      [ ]
    property int addIndex:              0
    property int connectIndex:          0
    property int disappearconnectIndex: 0
    property int disappearIndex:        0
    property bool beginDisappear:       false
    property bool beginConnectDisappear:false
    property real connectRecLen:        0
    property real rdHdPreviousX :       0
    property real rdHdPreviousY :       0
    property real rdHdCurrentX :        0
    property real rdHdCurrentY :        0
    property real angle:                0
    property real timerInterval:        400

    function creatObj(){
        var obj = tracePoint.createObject(parent,{x:tbmPos.coordinate_x, y:tbmPos.coordinate_y})
        return obj;
    }

    function creatConnectObj(){
        var obj = connectRec.createObject(parent,{x:(rdHdPreviousX + rdHdCurrentX - connectRecLen)/2 + 10, y:(rdHdPreviousY + rdHdCurrentY)/2})
        return obj;
    }

    function addPoint(){
        if(addIndex == 0){
            rdHdCurrentX = tbmPos.coordinate_x
            rdHdCurrentY = tbmPos.coordinate_y
        }
        else{
            rdHdPreviousX = rdHdCurrentX
            rdHdPreviousY = rdHdCurrentY
            rdHdCurrentX = tbmPos.coordinate_x
            rdHdCurrentY = tbmPos.coordinate_y
            connectRecLen = calLength()
            angle = rotangle()
            rdhdconnecttrace[connectIndex] = creatConnectObj()
            rdhdconnecttrace[connectIndex].width = connectRecLen
            rdhdconnecttrace[connectIndex].rotation = angle
            connectIndex++
            beginConnectDisappear = true
        }
        rdHeaderTrace[addIndex] = creatObj()
        addIndex++
        beginDisappear = true
        //加快消失速度
        if(addIndex >= 8)
        {
            timerInterval = 270
        }
    }

    function deletePoint(){
        rdHeaderTrace[disappearIndex].destroy()
        disappearIndex++
        if(disappearIndex >= addIndex){
            beginDisappear = false
        }
    }

    function deleteConnect(){
        rdhdconnecttrace[disappearconnectIndex].destroy()
        disappearconnectIndex++
        if(disappearconnectIndex >= connectIndex){
            beginConnectDisappear = false
        }
    }

    function calLength(){
        return Math.sqrt((rdHdPreviousX - rdHdCurrentX) * (rdHdPreviousX - rdHdCurrentX) + (rdHdPreviousY - rdHdCurrentY) * (rdHdPreviousY - rdHdCurrentY))
    }

    function rotangle(){
        if(rdHdCurrentY == rdHdPreviousY)
            return 0
        else
            return (Math.atan((rdHdCurrentY - rdHdPreviousY) / (rdHdCurrentX - rdHdPreviousX))) * 180 / Math.PI
    }

    function reset(){
        timerInterval = 600
        addIndex = 0
        connectIndex = 0
        disappearIndex = 0
        disappearconnectIndex = 0
        rdHeaderTrace.clear()
        rdhdconnecttrace.clear()
    }

    Component{
        id:tracePoint
        Rectangle{
            id:rdhdPoint
            height:20
            width:20
            radius: 10
            z:2
            color:"orange"
        }
    }

    Component{
        id:connectRec
        Rectangle{
            id:rdhdLine
            height: 20
            width: 20
            radius: 10
            color: "#fee140"
            z:1
            rotation: 0
        }
    }

    Timer{
        id:disappeartimer
        interval: timerInterval
        repeat: true
        running: beginDisappear
        onTriggered: {
            deletePoint()
        }
    }

    Timer{
        id:disappearConnecttimer
        interval: timerInterval
        repeat: true
        running: beginConnectDisappear
        onTriggered: {
            deleteConnect()
        }
    }

    Connections{
        target: tbmPos
        onCoordinateChanged:{
            addPoint()
        }
    }
}
