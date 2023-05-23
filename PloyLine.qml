import QtQuick 2.15
import QtQml 2.0

Canvas{
    id:linecanvas
    anchors.fill: parent
    property real currentx
    property real currenty
    property real previousx
    property real previousy
    property real angle
    property real count



    //计算箭头方位角
    function _updateArrowAngle() {
        var x = currentx-previousx
        var y = currenty-previousy
        angle = -Math.atan2(y,x)
    }


    onPaint: {
        var ctx = getContext("2d")
        var ctxArrow = getContext("2d")
        linecanvas._updateArrowAngle()

        ctx.beginPath()
        ctx.lineWidth = 1
        ctx.strokeStyle = "orange"
        ctx.moveTo(currentx, currenty)
        ctx.lineTo(previousx, previousy)
        ctx.closePath()
        ctx.stroke()

        if(count>=1){
        ctxArrow.lineWidth = 2
        ctxArrow.strokeStyle = "white"
        ctxArrow.beginPath();
        ctxArrow.moveTo((currentx+previousx)/2, (currenty+previousy)/2);
        ctxArrow.lineTo((currentx+previousx)/2-15*Math.cos(0.7854-angle),(currenty+previousy)/2-15*Math.sin(0.7854-angle));
        ctxArrow.stroke();
        ctxArrow.beginPath();
        ctxArrow.moveTo((currentx+previousx)/2, (currenty+previousy)/2);
        ctxArrow.lineTo((currentx+previousx)/2-15*Math.sin(0.7854-angle),(currenty+previousy)/2+15*Math.cos(0.7854-angle));
        ctxArrow.stroke();
        }
    }

}
//    Timer {
//            id: timer;
//            interval: 500;//设置定时器定时时间为500ms,默认1000ms
//            repeat: true //是否重复定时,默认为false
//            running: true //是否开启定时，默认是false，当为true的时候，进入此界面就开始定时
//            triggeredOnStart: false // 是否开启定时就触发onTriggered，一些特殊用户可以用来设置初始值。
//            onTriggered: {  //定时触发槽,定时完成一次就进入一次
//                linecanvas.requestPaint()
//                console.log("11")
//            }
//    }



