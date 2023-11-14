#include "TBM_Trace.h"
#include "QDebug"
TBM_Trace::TBM_Trace(QObject *parent)
    : QObject{parent}
{

}


void TBM_Trace::setCoordinate_x(const float x)
{
    coordinate_x = x;
    emit coordinate_xChanged();
}

void TBM_Trace::setCoordinate_y(const float y)
{
        coordinate_y = y;
        emit coordinate_yChanged();
        emit coordinateChanged();
}

//void TBM_Trace::setCoordinate_x(const float x)
//{
//    coordinate_x = x;
//    emit coordinate_xChanged();
//    //以下为测试部分
//    if(x_begindisappear)
//    {
//        setCoordinate_xdisappear(coordinate_xarr[xcount_past]);
//        xcount_past++;
//        if(xcount_past>=10)
//            xcount_past = 0;
//        emit coordinate_xdisappearChanged();
//    }
//    coordinate_xarr[xcount_current] = coordinate_x;
//    xcount_current++;
//    if(xcount_current>=10)
//    {
//        xcount_current = 0;
//        x_begindisappear = true;
//    }
//}

//void TBM_Trace::setCoordinate_y(const float y)
//{
//        coordinate_y = y;
//        emit coordinate_yChanged();
//        //以下为测试部分
//        if(y_begindisappear)
//        {
//            setCoordinate_ydisappear(coordinate_yarr[ycount_past]);
//            ycount_past++;
//            if(ycount_past>=10)
//                ycount_past = 0;
//            emit coordinate_ydisappearChanged();
//            emit coordinatedisappearChanged();
//        }
//        coordinate_yarr[ycount_current] = coordinate_y;
//        ycount_current++;
//        if(ycount_current>=10)
//        {
//            ycount_current = 0;
//            y_begindisappear = true;
//        }
//        emit coordinateChanged();
//}
