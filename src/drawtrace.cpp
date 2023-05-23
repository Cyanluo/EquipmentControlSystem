#include "drawtrace.h"


DrawTrace::DrawTrace()
{
    initServer();
}

DrawTrace::~DrawTrace()
{

}


void DrawTrace::setCoordinate_x(const quint16 _coordinate)
{
    //if(_coordinate!=coordinate_x)
    //{
        coordinate_x = _coordinate;

        //以下为测试部分
        if(x_begindisappear)
        {
            setCoordinate_xdisappear(coordinate_xarr[xcount_past]);
            xcount_past++;
            if(xcount_past>=10)
                xcount_past = 0;
            //emit coordinate_xdisappearChanged();
            //emit coordinatedisappearChanged();
        }
        coordinate_xarr[xcount_current] = coordinate_x;
        xcount_current++;
        if(xcount_current>=10)
        {
            xcount_current = 0;
            x_begindisappear = true;
        }

        // ///////////
       // emit coordinate_xChanged();
       // emit coordinateChanged();
    //}
    //else
        //return;
}



quint16 DrawTrace::currentcoordinate_x()
{
    return coordinate_x;
}

void DrawTrace::setCoordinate_y(const quint16 _coordinate)
{
    //if(_coordinate!=coordinate_y)
    //{
        coordinate_y = _coordinate;

        //以下为测试部分
        if(y_begindisappear)
        {
            setCoordinate_ydisappear(coordinate_yarr[ycount_past]);
            ycount_past++;
            if(ycount_past>=10)
                ycount_past = 0;
            emit coordinate_ydisappearChanged();
            emit coordinatedisappearChanged();
        }
        coordinate_yarr[ycount_current] = coordinate_y;
        ycount_current++;
        if(ycount_current>=10)
        {
            ycount_current = 0;
            y_begindisappear = true;
        }

        // ///////////

        emit coordinate_yChanged();
        emit coordinateChanged();

    //}
    //else
        //return;
}

quint16 DrawTrace::currentcoordinate_y()
{
    return coordinate_y;
}

void DrawTrace::setCoordinate_xdisappear(const quint16 _coordinate)
{
    //if(_coordinate!=coordinate_xdisappear)
    //{
        coordinate_xdisappear = _coordinate;
        //emit coordinate_xdisappearChanged();
        //emit coordinatedisappearChanged();

    //}
    //else
        //return;

}

void DrawTrace::setCoordinate_ydisappear(const quint16 _coordinate)
{
    //if(_coordinate!=coordinate_ydisappear)
    //{
        coordinate_ydisappear = _coordinate;
        //emit coordinate_ydisappearChanged();
        //emit coordinatedisappearChanged();

    //}
    //else
        //return;

}


quint16 DrawTrace::cuurentcoordinate_xdisappear()
{
    return coordinate_xdisappear;
}

quint16 DrawTrace::cuurentcoordinate_ydisappear()
{
    return coordinate_ydisappear;
}


void DrawTrace::initServer()
{
    //创建Server对象
    server = new QTcpServer(this);

    //
    QObject::connect(server, &QTcpServer::newConnection, this, &DrawTrace::slotNewConnected);

    //设置IP地址，端口号8234
    server->listen(QHostAddress::Any, 8234);


}

void DrawTrace::slotNewConnected()
{
    while(server->hasPendingConnections())
       {
           socket = server->nextPendingConnection();
           connect(socket, &QTcpSocket::readyRead, this, &DrawTrace::slotReadyRead);
           connect(socket, &QTcpSocket::disconnected, socket, &QObject::deleteLater);
           qDebug("[%s:%d] connected", socket->peerAddress().toString().toStdString().c_str(), socket->peerPort());
       }
}

void DrawTrace::slotReadyRead()
{

    if(socket->bytesAvailable()<=0)
        return;
    //const QString recv_text=QString::fromUtf8(socket->readAll());
    QByteArray dataBuff = socket->readAll();

    quint8 x1 = (quint8)dataBuff[0];
    quint8 x2 = (quint8)dataBuff[1];
    quint16 x = x1 + x2*256;          //计算距离值
    x = x/2;

    if((quint8)dataBuff[2]==1)
    {
        setCoordinate_x(x);
    }
    else
    {
        setCoordinate_y(x);
    }
}
