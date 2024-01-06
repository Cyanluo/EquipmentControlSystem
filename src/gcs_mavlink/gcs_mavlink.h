#ifndef GCS_MAVLINK_H
#define GCS_MAVLINK_H

#include <QObject>
#include <ardupilotmega/mavlink.h>
#include "MAVLinkProtocol.h"
#include "NetworkUDP.h"
#include "seriallink.h"
#include "AbstractIO.h"

class GCS_Mavlink :public QObject
{
    Q_OBJECT
public:
    GCS_Mavlink();

    void sendData(const char *bytes, int length);
    Q_INVOKABLE QString ioType();
    Q_INVOKABLE void setIOType(QString iotype);
    Q_INVOKABLE void getConnectInfo(QString info);
    Q_INVOKABLE void open();
    Q_INVOKABLE void close();

    Q_INVOKABLE bool isGCSEncipher() {return _mavprotocol->enEncipher();}
    Q_INVOKABLE void setEncipher(bool enable) {_mavprotocol->setEncipher(enable);}

signals:
    void received(mavlink_message_t msg);

public slots:
    void handle_inter(mavlink_message_t msg);
    AbstractIO* getLink();

protected:
    MAVLinkProtocol* _mavprotocol = new MAVLinkProtocol;
    AbstractIO* _link = nullptr;
};

#endif // GCS_MAVLINK_H
