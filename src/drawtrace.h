#ifndef DRAWTRACE_H
#define DRAWTRACE_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QObject>

class DrawTrace :public QObject
{
    Q_OBJECT
public:
    DrawTrace();
    ~DrawTrace();
    Q_PROPERTY(quint16 coordinate_x READ currentcoordinate_x WRITE setCoordinate_x NOTIFY coordinate_xChanged)
    Q_PROPERTY(quint16 coordinate_y READ currentcoordinate_y WRITE setCoordinate_y NOTIFY coordinate_yChanged)
    Q_PROPERTY(quint16 coordinate_xdisappear READ cuurentcoordinate_xdisappear WRITE setCoordinate_xdisappear NOTIFY coordinate_xdisappearChanged)
    Q_PROPERTY(quint16 coordinate_ydisappear READ cuurentcoordinate_ydisappear WRITE setCoordinate_ydisappear NOTIFY coordinate_ydisappearChanged)
    void setCoordinate_x(const quint16 _coordinate);
    quint16 currentcoordinate_x();

    void setCoordinate_y(const quint16 _coordinate);
    quint16 currentcoordinate_y();

    void setCoordinate_xdisappear(const quint16 _coordinate);
    quint16 cuurentcoordinate_xdisappear();

    void setCoordinate_ydisappear(const quint16 _coordinate);
    quint16 cuurentcoordinate_ydisappear();

private:
    void initServer(void);

    //槽函数
    void slotNewConnected(void);
    void slotReadyRead(void);

signals:
    void coordinate_xChanged();
    void coordinate_yChanged();
    void coordinate_xdisappearChanged();
    void coordinate_ydisappearChanged();
    void coordinateChanged();
    void coordinatedisappearChanged();


private:
    QString recivedata;
    QTcpServer *server;
    QTcpSocket *socket;
    quint16 coordinate_x;
    quint16 coordinate_y;
    // ceshi
    quint16 coordinate_xarr[10];
    quint16 coordinate_yarr[10];
    int xcount_current = 0;
    int xcount_past = 0;
    bool x_begindisappear = false;
    int ycount_current = 0;
    int ycount_past = 0;
    bool y_begindisappear = false ;
    quint16 coordinate_xdisappear;
    quint16 coordinate_ydisappear;
    // //

};

#endif // DRAWTRACE_H
