import QtQuick 2.15
import QtQuick.Window 2.15

import setcd 1.0
Rectangle{
    id: root
    anchors.fill: parent

    visible: true
    property real carPreviousX :   -1
    property real carPreviousY :   -1
    property real carCurrentX :    -1
    property real carCurrentY :    -1
    property real missionindex :   0
    property real countpoint :     0

    //测试
    property real carPreviousX_D :   -1
    property real carPreviousY_D :   -1
    property real carCurrentX_D :    -1
    property real carCurrentY_D :    -1
    property real countpoint_D :     0
    ////////////////////////////////

    Canvas{
        id: mapCanvas
        anchors.fill: parent

        onPaint: {
            var ctxLine = getContext("2d")
            //画线
            if(carCurrentX !== -1)
            {
                drawLine(ctxLine)
            }
            var ctxCircle = getContext("2d")
            //画点
            if(carPreviousX !== -1)
            {
                drawCircle(ctxCircle)
            }

            //画消失效果
            var ctxLine_D = getContext("2d")
            //画线
            if(carCurrentX_D !== -1)
            {
                ctxLine_D.strokeStyle = "white"
                drawLine_D(ctxLine_D)
            }
            var ctxCircle_D = getContext("2d")
            //画点
            if(carPreviousX_D !== -1)
            {
                drawCircle_D(ctxCircle_D)
            }

        }

        //绘制线
        function drawLine(ctx)
        {
            ctx.beginPath()
            ctx.lineWidth = 1
            ctx.strokeStyle = "black"
            ctx.moveTo(carPreviousX*10, carPreviousY*10)
            ctx.lineTo(carCurrentX*10, carCurrentY*10)
            ctx.closePath()
            ctx.stroke()
        }
        //绘制点
        function drawCircle(ctx)
        {
            //说明是第一个点
            if(carCurrentX === -1)
            {
                ctx.beginPath();
                ctx.arc(carPreviousX*10,carPreviousY*10,10,0,2*Math.PI)
                ctx.closePath();
                ctx.fillStyle="orange"
                ctx.font = "15px sans-serif"
                //ctx.text(missionindex,carPreviousX*10,carPreviousY*10)
                ctx.fill();
            }
            else
            {
                ctx.beginPath();
                ctx.arc(carCurrentX*10,carCurrentY*10,10,0,2*Math.PI)
                ctx.closePath();
                ctx.fillStyle="orange"
                ctx.font = "15px sans-serif"
                //ctx.text(missionindex,carCurrentX*10,carCurrentY*10)
                ctx.fill();
            }
        }

        //画消失线
        function drawLine_D(ctx)
        {
            ctx.beginPath()
            ctx.lineWidth = 2
            ctx.strokeStyle = "white"
            ctx.moveTo(carPreviousX_D*10, carPreviousY_D*10)
            ctx.lineTo(carCurrentX_D*10, carCurrentY_D*10)
            ctx.closePath()
            ctx.stroke()
        }
        //画消失点
        function drawCircle_D(ctx)
        {
            //说明是第一个点
            if(carCurrentX_D === -1)
            {
                ctx.beginPath();
                ctx.arc(carPreviousX_D*10,carPreviousY_D*10,10,0,2*Math.PI)
                ctx.closePath();
                ctx.fillStyle = "white"
                ctx.strokeStyle = "white"
                ctx.font = "15px sans-serif"
                //ctx.text(missionindex,carPreviousX_D*10,carPreviousY_D*10)
                ctx.fill();
                ctx.stroke();
            }
            else
            {
                ctx.beginPath();
                ctx.arc(carCurrentX_D*10,carCurrentY_D*10,10,0,2*Math.PI)
                ctx.closePath();
                ctx.fillStyle="white"
                ctx.strokeStyle = "white"
                ctx.font = "15px sans-serif"
                //ctx.text(missionindex,carCurrentX_D*10,carCurrentY_D*10)
                ctx.fill();
                ctx.stroke();
            }
        }


        function addindex() {
            missionindex = missionindex + 1
        }
        function addcountpoint() {
            countpoint = countpoint + 1
        }
        function addcountpoint_D() {
            countpoint_D = countpoint_D + 1
        }





        SettingCoordinate{

            onCoordinateChanged:  {
                //mapCanvas.addindex()
                mapCanvas.addcountpoint()
                console.log("current",coordinate_x,coordinate_y)

                //如果是第一个点
                if(carPreviousX === -1)
                {
                    carPreviousX = coordinate_x;
                    carPreviousY = coordinate_y;
                }
                else
                {
                    //如果是第二个点
                    if(carCurrentX === -1)
                    {
                        carCurrentX = coordinate_x;
                        carCurrentY = coordinate_y;
                    }
                    else
                    {
                        //记录并更新每次的点
                        carPreviousX = carCurrentX;
                        carPreviousY = carCurrentY;
                        carCurrentX = coordinate_x;
                        carCurrentY = coordinate_y;
                    }
                }
                if(countpoint >=5)
                mapCanvas.requestPaint();
            }

            //画消失部分
            onCoordinatedisappearChanged: {
                mapCanvas.addcountpoint_D()
                console.log("disappear",coordinate_xdisappear,coordinate_ydisappear)


                //如果是第一个点
                if(carPreviousX_D === -1)
                {
                    carPreviousX_D = coordinate_xdisappear;
                    carPreviousY_D = coordinate_ydisappear;
                }
                else
                {
                    //如果是第二个点
                    if(carCurrentX_D === -1)
                    {
                        carCurrentX_D = coordinate_xdisappear;
                        carCurrentY_D = coordinate_ydisappear;
                    }
                    else
                    {
                        //记录并更新每次的点
                        carPreviousX_D = carCurrentX_D;
                        carPreviousY_D = carCurrentY_D;
                        carCurrentX_D = coordinate_xdisappear;
                        carCurrentY_D = coordinate_ydisappear;
                    }
                }
                if(countpoint_D >=5)              //此处需要改动
                mapCanvas.requestPaint();
            }                      

       }
  }
}


