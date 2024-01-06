#ifndef MAVLINKPROTOCOL_H
#define MAVLINKPROTOCOL_H

#include <QObject>
#include <ardupilotmega/mavlink.h>
#include "src/Encipher/AESEncipher.h"
#include <QTimer>

class MAVLinkProtocol:public QObject
{
    Q_OBJECT
public:
    MAVLinkProtocol();

    bool encrypt(uint8_t* &dest_buff, const uint8_t *src_buff, uint32_t& len);
    bool enEncipher();
    void setEncipher(bool enable) {_encipher.setEnable(enable);}

signals:
    void messageReceived(mavlink_message_t message);
public slots:
    void prepare(QByteArray b);
    void parse();

protected:
    mavlink_message_t _message;
    mavlink_status_t _status;

    AESEncipher _encipher;
    AESAssembler _assembler;

    QTimer      * parseTimer            = new QTimer(this);
};

#endif // MAVLINKPROTOCOL_H
