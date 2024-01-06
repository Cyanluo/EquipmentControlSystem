#ifndef NETWORKUDP_H
#define NETWORKUDP_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include "AbstractIO.h"

class UDPCLient {
public:
    UDPCLient(const QHostAddress& address_, quint16 port_)
        : address(address_)
        , port(port_)
    {}
    UDPCLient(const UDPCLient* other)
        : address(other->address)
        , port(other->port)
    {}
    QHostAddress    address;
    quint16         port;
};

class NetworkUDP : public AbstractIO
{
    Q_OBJECT
public:
    explicit NetworkUDP(QObject *parent = nullptr);

    void sendData(const char *bytes, int length) override;
    QString IOType() override { return "UDP"; }
    void getConnectInfo(QString& info) override;
    void open() override;
    void close() override;

    ~NetworkUDP() override;

signals:
    void udpConnectChanged();
    void updConnected();
    void udpClosed();

private slots:
    void readMessage();

private:
    QUdpSocket* UdpSocket = nullptr;                    //UPD 发送套接字
    QHostAddress    _ipAddr;                            //本地ip
    quint16         _port;                              //本地端口
    bool            ipAndPortValid = false;
    QHostAddress    _destIpAddr;                        //目标ip
    quint16         _destPort;                          //目标端口

};

#endif // NETWORKUDP_H
