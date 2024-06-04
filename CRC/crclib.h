#ifndef CRCLIB_H
#define CRCLIB_H

#include <QByteArray>

class CRC32Calculator
{
public:
    CRC32Calculator();
    void addData(const QByteArray& data);
    uint32_t getResult() const;
    void reset();

private:
    uint32_t crc;
};

#endif // CRCLIB_H
