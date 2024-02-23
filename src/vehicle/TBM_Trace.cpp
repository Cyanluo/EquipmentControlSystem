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
