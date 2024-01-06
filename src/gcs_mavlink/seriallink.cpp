#include "seriallink.h"
#include <QDebug>

SerialLink::SerialLink(QObject *parent)
    : AbstractIO{parent}
{
    connect(_port, &QIODevice::readyRead, this, &SerialLink::_readBytes);
    connect(_port, &QSerialPort::errorOccurred,this,&SerialLink::handleError);
    connect(timer, &QTimer::timeout, this, &SerialLink::callCheckPort);
}

void SerialLink::open()
{
    //设置串口名
    _port->setPortName(port);
    //设置波特率
    _port->setBaudRate(buadRate);
    //设置数据位数
    _port->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    _port->setParity(QSerialPort::NoParity);
    //设置停止位
    _port->setStopBits(QSerialPort::OneStop);
    //设置流控制
    _port->setFlowControl(QSerialPort::NoFlowControl);

    timer->start(1000);
}

void SerialLink::close()
{
    if(_port->isOpen())
    {
        _port->close();
        timer->stop();
        emit disConnected();
    }
}

void SerialLink::getConnectInfo(QString& info)
{
    QStringList infos = info.split(QLatin1Char(','), Qt::SkipEmptyParts);

    port = infos[0];

    bool ok;
    buadRate   = infos[1].toUInt(&ok, 10);
    if(!ok && _port)
    {
        qDebug()<<"convert buadRate to int err";
        return;
    }
}

void SerialLink::sendData(const char *bytes, int length)
{
    QByteArray byteArray(bytes,length);
    _port->write(byteArray);
}

void SerialLink::_readBytes(void)
{
    if (_port && _port->isOpen()) {
        qint64 byteCount = _port->bytesAvailable();
        if (byteCount) {
            QByteArray buffer;
            buffer.resize(byteCount);
            _port->read(buffer.data(), buffer.size());
            emit bytesReceived(buffer);
        }
    }
}

void SerialLink::callCheckPort()
{
    checkAvailablePort();
}

void SerialLink::handleError(QSerialPort::SerialPortError error)
{
    if(error == QSerialPort::ResourceError){
        return;
    }
}

void SerialLink::checkAvailablePort()
{
    if(!_port->isOpen())
    {
        if(_port->open(QIODevice::ReadWrite))
        {
            emit connected();
        }
    }
}

SerialLink::~SerialLink()
{
    SerialLink::close();
}
