#include "gcs_mavlink.h"
#include "NetworkUDP.h"
#include "seriallink.h"
#include <QDebug>

GCS_Mavlink::GCS_Mavlink(ECSApplication* app, ECSToolbox* toolbox)
    :ECSTool(app, toolbox)
{
    setIOType("UDP");
}

void GCS_Mavlink::handle_inter(mavlink_message_t msg)
{
    emit received(msg);
}

void GCS_Mavlink::sendData(const char *bytes, int length)
{
    uint8_t* dest = nullptr;
    uint32_t len = length;

    if(_mavprotocol->enEncipher())
    {
        if(_mavprotocol->encrypt(dest, (uint8_t*)bytes, len))
        {
            _link->sendData((char*)dest, len);
            delete[] dest;
        }
    }
    else
    {
        _link->sendData(bytes, length);
    }
}

AbstractIO* GCS_Mavlink::getLink()
{
    return _link;
}

QString GCS_Mavlink::ioType()
{
    return _link->IOType();
}

void GCS_Mavlink::setIOType(QString iotype)
{
    disconnect(_link, &AbstractIO::bytesReceived, _mavprotocol, &MAVLinkProtocol::prepare);
    disconnect(_mavprotocol, &MAVLinkProtocol::messageReceived, this, &GCS_Mavlink::handle_inter);

    if(iotype == "UDP")
    {
        delete _link;
        _link = new NetworkUDP();
    }
    else if(iotype == "Serial")
    {
        delete _link;
        _link = new SerialLink();
    }
    else
    {
        qDebug() << "invalid iotype";
        return;
    }

    connect(_link, &AbstractIO::bytesReceived, _mavprotocol, &MAVLinkProtocol::prepare);
    connect(_mavprotocol, &MAVLinkProtocol::messageReceived, this, &GCS_Mavlink::handle_inter);
}

void GCS_Mavlink::getConnectInfo(QString info)
{
    _link->getConnectInfo(info);
}

void GCS_Mavlink::open()
{
    _link->open();
}

void GCS_Mavlink::close()
{
    _link->close();
}
