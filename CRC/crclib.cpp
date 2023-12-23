#include "crclib.h"

CRC32Calculator::CRC32Calculator() : crc(0xFFFFFFFF) {}

void CRC32Calculator::addData(const QByteArray& data)
{
    const uint8_t* dataPtr = reinterpret_cast<const uint8_t*>(data.constData());
    uint16_t length = static_cast<uint16_t>(data.size());
    while (length--)
    {
        crc ^= *dataPtr++;
        for (uint8_t i = 0; i < 8; ++i)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc = (crc >> 1);
        }
    }
}

uint32_t CRC32Calculator::getResult() const
{
    return ~crc;
}
