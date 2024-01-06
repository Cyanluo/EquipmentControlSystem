#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <QObject>
#include <QSerialPort>
#include <QString>
#include <QTimer>
#include <QSerialPortInfo>
#include "AbstractIO.h"

class SerialLink : public AbstractIO
{
    Q_OBJECT
public:
    explicit SerialLink(QObject *parent = nullptr);

    void sendData(const char *bytes, int length) override;
    QString IOType() override { return "Serial"; }
    void getConnectInfo(QString& info) override;
    void open() override;
    void close() override;

    ~SerialLink() override;

private slots:
    void _readBytes         (void);
    void callCheckPort      (void);
    void handleError    (QSerialPort::SerialPortError error);

private:
    void checkAvailablePort();

private:
    QSerialPort * _port            = new QSerialPort;
    QTimer      * timer            = new QTimer(this);
    bool          isPortOpen       = false;
    QString       port;
    int           buadRate;
};

#endif // SERIALLINK_H
