#include "seriallink.h"
#include <QDebug>

SerialLink::SerialLink(QObject *parent)
    : QObject{parent}
{
    //设置串口名
    _port->setPortName("COM11");
    //设置波特率
    _port->setBaudRate(QSerialPort::Baud115200);
    //设置数据位数
    _port->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
     _port->setParity(QSerialPort::NoParity);
    //设置停止位
    _port->setStopBits(QSerialPort::OneStop);
    //设置流控制
    _port->setFlowControl(QSerialPort::NoFlowControl);

    connect(timer, &QTimer::timeout, this, &SerialLink::callCheckPort);
    timer->start(1000);

    connect(_port, &QIODevice::readyRead, this, &SerialLink::_readBytes);
    connect(_port, &QSerialPort::errorOccurred,this,&SerialLink::closeSerialPort);
}

void SerialLink::sendMavlinkMessage(const char *bytes, int length)
{
    QByteArray byteArray(bytes,length);
    //qDebug()<<byteArray[0]<<byteArray[1]<<byteArray[2]<<byteArray[3]<<byteArray[4]<<byteArray[5]<<byteArray[6];
    _port->write(byteArray);
}

void SerialLink::_readBytes(void)
{
    //qDebug()<<"in _readBytes()";
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

void SerialLink::closeSerialPort(QSerialPort::SerialPortError error)
{
    if(error == QSerialPort::ResourceError){
        _port->close();
    }
}

void SerialLink::checkAvailablePort()
{
    //qDebug()<<"serial is open? "<<_port->isOpen();
    if(!_port->isOpen())
        _port->open(QIODevice::ReadWrite);
}
