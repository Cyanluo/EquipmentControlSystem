#ifndef TBM_TRACE_H
#define TBM_TRACE_H

#include <QObject>

class TBM_Trace : public QObject
{
    Q_OBJECT

public:
    explicit TBM_Trace(QObject *parent = nullptr);
    Q_PROPERTY(quint16 coordinate_x READ currentcoordinate_x WRITE setCoordinate_x NOTIFY coordinate_xChanged)
    Q_PROPERTY(quint16 coordinate_y READ currentcoordinate_y WRITE setCoordinate_y NOTIFY coordinate_yChanged)
    Q_PROPERTY(quint16 coordinate_xdisappear READ cuurentcoordinate_xdisappear WRITE setCoordinate_xdisappear NOTIFY coordinate_xdisappearChanged)
    Q_PROPERTY(quint16 coordinate_ydisappear READ cuurentcoordinate_ydisappear WRITE setCoordinate_ydisappear NOTIFY coordinate_ydisappearChanged)
    void setCoordinate_x(const float x);

    float currentcoordinate_x()                               {   return coordinate_x;}

    void setCoordinate_y(const float y);

    float currentcoordinate_y()                               {   return coordinate_y;}

    void setCoordinate_xdisappear(const float x)              {   coordinate_xdisappear = x;
                                                                    emit coordinate_xdisappearChanged();}

    float cuurentcoordinate_xdisappear()                      {   return coordinate_xdisappear;}

    void setCoordinate_ydisappear(const float y)              {   coordinate_ydisappear = y;
                                                                    emit coordinate_ydisappearChanged();}

    float cuurentcoordinate_ydisappear()                      {   return coordinate_ydisappear;}

signals:
    void coordinate_xChanged();
    void coordinate_yChanged();
    void coordinate_xdisappearChanged();
    void coordinate_ydisappearChanged();
    void coordinateChanged();
    void coordinatedisappearChanged();

private:
    float coordinate_x;
    float coordinate_y;
    float coordinate_xdisappear;
    float coordinate_ydisappear;
    float coordinate_xarr[10];
    float coordinate_yarr[10];
    int xcount_current = 0;
    int xcount_past = 0;
    bool x_begindisappear = false;
    int ycount_current = 0;
    int ycount_past = 0;
    bool y_begindisappear = false ;
};

#endif // TBM_TRACE_H


