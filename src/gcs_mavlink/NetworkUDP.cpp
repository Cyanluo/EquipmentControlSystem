#include "NetworkUDP.h"

NetworkUDP::NetworkUDP(QObject *parent)
    : AbstractIO{parent}
{
}

//槽函数，接收读到的udp数据
void NetworkUDP::readMessage()
{
    QByteArray  databuffer;
    while(UdpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(UdpSocket->pendingDatagramSize());  //每次循环中，使用待处理数据报文的大小创建一个datagram
        qint64 slen = UdpSocket->readDatagram(datagram.data(), datagram.size(), &_destIpAddr, &_destPort);

        if (slen == -1) {
            qDebug()<<"slen == -1";
            break;
        }

        databuffer.append(datagram);
        if(databuffer.size() > 50)
        {
            //发送需要处理数据信号
            emit bytesReceived(databuffer);
            databuffer.clear();
        }
    }

    emit bytesReceived(databuffer);
}

void NetworkUDP::sendData(const char *bytes, int length)
{
    if(!ipAndPortValid)
    {
        return;
    }
    QByteArray datagram(bytes,length);
    UdpSocket->writeDatagram(datagram, _destIpAddr, _destPort);
}

void NetworkUDP::getConnectInfo(QString& info)
{
    QStringList infos = info.split(QLatin1Char(','), Qt::SkipEmptyParts);

    _ipAddr = QHostAddress(infos[0]);
    bool ok;
    _port   = infos[1].toUInt(&ok, 10);
    if(!ok && _port)
    {
        qDebug()<<"convert port to int err";
        return;
    }
}

void NetworkUDP::open()
{
    UdpSocket = new QUdpSocket(this);

    if(!UdpSocket->isOpen())
    {
        UdpSocket->open(QIODevice::ReadWrite);
    }
    qDebug() << _ipAddr.toString() << ":" << _port;
    if(UdpSocket->bind(_ipAddr, _port))
    {
        connect(UdpSocket, &QUdpSocket::readyRead, this, &NetworkUDP::readMessage);

        ipAndPortValid = true;
        emit connected();
    }
    else
    {
        qDebug() << "fail to bind udp";
    }
}

void NetworkUDP::close()
{
    if(UdpSocket != nullptr)
    {
        disconnect(UdpSocket,&QUdpSocket::readyRead,this,&NetworkUDP::readMessage);
        UdpSocket->disconnectFromHost();
        UdpSocket->close();
        UdpSocket->abort();
        delete UdpSocket;
        UdpSocket = nullptr;
        ipAndPortValid = false;
        emit disConnected();
    }
}

NetworkUDP::~NetworkUDP()
{
    NetworkUDP::close();
}
