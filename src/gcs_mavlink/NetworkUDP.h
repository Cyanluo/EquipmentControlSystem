#ifndef NETWORKUDP_H
#define NETWORKUDP_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

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

class NetworkUDP : public QObject
{
    Q_OBJECT
public:
    explicit NetworkUDP(QObject *parent = nullptr);

    //Q_PROPERTY(bool udpConnect READ getUdpConnect WRITE setUdpConnect NOTIFY udpConnectChanged)

//    Q_INVOKABLE void udpSendData();     //Udp发送数据--test
    Q_INVOKABLE void getIpAndPort(QString ipaddr, QString portname);
    Q_INVOKABLE void udpClose();                                    //关闭udp

    //bool getUdpConnect()                            {return udpConnect;}
    //void setUdpConnect(bool isconnect)              {udpConnect = isconnect;}
    void sendMavlinkMessage(const char *bytes, int length);

public:
    //bool udpConnect = false;

signals:
    void udpConnectChanged();
    void updConnected();
    void udpClosed();
    void bytesReceived(QByteArray data);

private slots:
    void readMessage();

private:
    //私有函数
    bool udpBind();                                     //udp套接字绑定IP地址与端口号

private:
    //私有变量
    QUdpSocket* UdpSocket = new QUdpSocket(this);       //UPD 发送套接字
    QHostAddress    _ipAddr;                            //目标ip
    quint16         _port;                              //目标端口
    bool            ipAndPortValid = false;
};

#endif // NETWORKUDP_H
