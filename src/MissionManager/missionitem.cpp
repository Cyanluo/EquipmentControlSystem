#include "missionitem.h"

missionitem::missionitem()
{


}

int missionitem::getNumber_x() const
{
    return number_x;
}

void missionitem::setNumber_x(int i)
{
    number_x = i;
    prenumber_x = number_x;
}

int missionitem::getNumber_y() const
{
    return number_y;
}

void missionitem::setNumber_y(int i)
{
    number_y = i;
    prenumber_y = number_y;
    emit number_yChanged();
}

int missionitem::getMissionindex() const
{
    return missionindex;
}

void missionitem::setMissionindex(int i)
{
    missionindex = i;
}

bool missionitem::getfocus()
{
    return focus;
}

void missionitem::setfocus(bool isfocus)
{
    focus = isfocus;
    emit focusChanged();
}

int missionitem::getPrenumber_x()
{
    return prenumber_x;

}
int missionitem::getPrenumber_y()
{
    return prenumber_y;
}

void missionitem::setPrenumber_x(int x)
{
    prenumber_x = x;
}

void missionitem::setPrenumber_y(int y)
{
    prenumber_y = y;
}


