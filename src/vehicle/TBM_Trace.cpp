#include "TBM_Trace.h"

TBM_Trace::TBM_Trace(QObject *parent)
    : QObject{parent}
{

}

void TBM_Trace::setCoordinate_x(const float x)
{
    if(coordinate_x == x)
    {
        return;
    }
    coordinate_x = x;
    emit coordinate_xChanged();
}

void TBM_Trace::setCoordinate_y(const float y)
{
    if(coordinate_y == y)
    {
        return;
    }
    coordinate_y = y;
    emit coordinate_yChanged();
    emit coordinateChanged();
}
