#ifndef ABSTRACTIO_H
#define ABSTRACTIO_H

#include <QObject>

class AbstractIO : public QObject
{
    Q_OBJECT
public:
    explicit AbstractIO(QObject *parent = nullptr): QObject(parent) {}

    virtual void sendData(const char *bytes, int length) = 0;
    virtual QString IOType() = 0;
    virtual void getConnectInfo(QString& info) = 0;
    virtual void open() = 0;
    virtual void close() = 0;

    virtual ~AbstractIO() {}

signals:
    void bytesReceived(QByteArray& s);
    void connected();
    void disConnected();
};

#endif // ABSTRACTIO_H
