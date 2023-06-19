#include "NetworkUDP.h"

NetworkUDP::NetworkUDP(QObject *parent)
    : QObject{parent}
{
//        UdpSocket->bind(QHostAddress("127.0.0.1"),5555);
//        connect(UdpSocket,&QUdpSocket::readyRead,this,&NetworkUDP::readMessage);
}


//槽函数，接收读到的udp数据
void NetworkUDP::readMessage()
{
    qDebug()<<"readMessage success!";
    QByteArray  databuffer;
    while(UdpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(UdpSocket->pendingDatagramSize());  //每次循环中，使用待处理数据报文的大小创建一个datagram
        quint16 senderPort;                                 //存储发送方的端口号
        QHostAddress sender;                                //存储发送方的IP地址
        qint64 slen = UdpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        //UdpSocket->errorString();
        if (slen == -1) {
            qDebug()<<"slen == -1";
            break;
        }
        databuffer.append(datagram);
        if(databuffer.size() > 10 *1024)         //10 *1024是自己设定的一个阈值，控制信号发送频率，不至于太快
        {
            //发送需要处理数据信号
            emit bytesReceived(databuffer);
            //qDebug()<<"databuffer的大小："<<databuffer.size();
            databuffer.clear();
        }
    }
    qDebug()<<"sizeof databuffer:"<<databuffer.size();
    qDebug()<<"databuffer.count:"<<databuffer.count();
    emit bytesReceived(databuffer);
}

bool NetworkUDP::udpBind()
{
    bool isbind;
    //QHostAddress host = QHostAddress::AnyIPv4;
    isbind = UdpSocket->bind(/*host*/QHostAddress("192.168.137.1"),14550);
    connect(UdpSocket,&QUdpSocket::readyRead,this,&NetworkUDP::readMessage);
    return isbind;
}

void NetworkUDP::udpClose()
{
    disconnect(UdpSocket,&QUdpSocket::readyRead,this,&NetworkUDP::readMessage);
    UdpSocket->close();
    ipAndPortValid = false;
    emit udpClosed();
}

void NetworkUDP::sendMavlinkMessage(const char *bytes, int length)
{
    if(!ipAndPortValid)
    {
        return;
    }
    QByteArray datagram(bytes,length);
    UdpSocket->writeDatagram(datagram, _ipAddr, _port);
    qDebug()<<"mavlink send success!-use udp";
}

//udp发送数据函数
//void NetworkUDP::udpSendData()
//{
//    QByteArray datagram{"This is a test message!"};
//    UdpSocket->writeDatagram(datagram, _ipAddr, _port);
//    qDebug()<<"send success!";
//}

//从qml获取IP地址与端口号
void NetworkUDP::getIpAndPort(QString ipaddr, QString portname)
{
    if(nullptr == ipaddr || nullptr == portname)
    {
        qDebug()<<"ip or port failure";
        return;
    }
    qDebug()<<"ipaddr:"<<ipaddr<<"//portname"<<portname;
    _ipAddr = QHostAddress(ipaddr);
    bool ok;
    _port   = portname.toUInt(&ok,10);
    if(!ok && _port)
    {
        qDebug()<<"convert port to int err";
        return;
    }
    //udpConnect = true;          //转换正常则正常连接
    //这里的bind与qml读的ip和端口号无关，只是监听本机收数据的端口
    if(udpBind())
    {
        ipAndPortValid = true;
        emit updConnected();
    }
}


