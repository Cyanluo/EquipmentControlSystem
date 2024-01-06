#include "MAVLinkProtocol.h"
#include <QDebug>

MAVLinkProtocol::MAVLinkProtocol()
{
    connect(parseTimer, &QTimer::timeout, this, &MAVLinkProtocol::parse);
    parseTimer->start(1);
}

void MAVLinkProtocol::prepare(QByteArray b)
{
    if(!_encipher.isEnable())
    {
        for (uint8_t position = 0; position < (uint8_t)b.size(); position++)
        {
            if (mavlink_parse_char(1, (uint8_t)b.data()[position], &_message, &_status))
            {
                emit messageReceived(_message);
            }
        }
    }
    else
    {
        _assembler.prepare((uint8_t*)b.data(), b.size());
    }
}

void MAVLinkProtocol::parse()
{
    AESAssembler::Message msg;
    uint8_t* decrypt_buff = nullptr;

    if(_encipher.isEnable())
    {
        if(_assembler.parse(msg))
        {
            if(_encipher.aes_decrypt(decrypt_buff, msg.payload, msg.length))
            {
                for (uint8_t position = 0; position < (uint8_t)msg.length; position++)
                {
                    if (mavlink_parse_char(1, decrypt_buff[position], &_message, &_status))
                    {
                        emit messageReceived(_message);
                    }
                }

                delete[] decrypt_buff;
            }

            delete[] msg.payload;
        }
    }
}

bool MAVLinkProtocol::encrypt(uint8_t* &dest_buff, const uint8_t *src_buff, uint32_t& len)
{
    return _encipher.aes_encrypt(dest_buff, src_buff, len);
}

bool MAVLinkProtocol::enEncipher()
{
    return _encipher.isEnable();
}
