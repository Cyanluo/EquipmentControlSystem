#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    initServer();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setCoordinate_x(const quint16 _coordinate)
{
    if(_coordinate!=coordinate_x)
    {
        coordinate_x = _coordinate;
        emit coordinate_xChanged();

    }
    else
        return;
}



quint16 MainWindow::currentcoordinate_x()
{
    return coordinate_x;
}

void MainWindow::setCoordinate_y(const quint16 _coordinate)
{
    if(_coordinate!=coordinate_y)
    {
        coordinate_y = _coordinate;
        emit coordinate_yChanged();

    }
    else
        return;
}

quint16 MainWindow::currentcoordinate_y()
{
    return coordinate_y;
}
void MainWindow::initServer()
{
    //创建Server对象
    server = new QTcpServer(this);

    //
    QObject::connect(server, &QTcpServer::newConnection, this, &MainWindow::slotNewConnected);

    //设置IP地址，端口号8234
    server->listen(QHostAddress::Any, 8234);


}

void MainWindow::slotNewConnected()
{
    while(server->hasPendingConnections())
       {
           socket = server->nextPendingConnection();
           connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
           connect(socket, &QTcpSocket::disconnected, socket, &QObject::deleteLater);
           qDebug("[%s:%d] connected", socket->peerAddress().toString().toStdString().c_str(), socket->peerPort());
       }
}

void MainWindow::slotReadyRead()
{

    if(socket->bytesAvailable()<=0)
        return;
    //const QString recv_text=QString::fromUtf8(socket->readAll());
    QByteArray dataBuff = socket->readAll();

    quint8 x1 = (quint8)dataBuff[0];
    quint8 x2 = (quint8)dataBuff[1];
    quint16 x = x1 + x2*256;
//    QString Volt = recv_text.mid(0,4);
//    QString I = recv_text.mid(4,4);
//    QString Temp = recv_text.mid(8,2);

    if((quint8)dataBuff[2]==1)
    {
        setCoordinate_x(x);
        //ui->lineEdit->setText(QString::number(x));
    }
    else
    {
        setCoordinate_y(x);
        //ui->lineEdit_2->setText(QString::number(x));
    }
    qDebug()<<x;
    qDebug()<<x1;
    qDebug()<<x2;



}
