#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <QObject>
#include <QSerialPort>
#include <QString>
#include <QTimer>
#include <QSerialPortInfo>

class SerialLink : public QObject
{
    Q_OBJECT
public:
    explicit SerialLink(QObject *parent = nullptr);

    void sendMavlinkMessage(const char *bytes, int length);

signals:
    void bytesReceived      (QByteArray data);

private slots:
    void _readBytes         (void);
    void callCheckPort      (void);
    void closeSerialPort    (QSerialPort::SerialPortError error);

private:
    void checkAvailablePort();

private:
    QSerialPort * _port            = new QSerialPort;
    QTimer      * timer            = new QTimer(this);
    bool          isPortOpen       = false;

};

#endif // SERIALLINK_H
