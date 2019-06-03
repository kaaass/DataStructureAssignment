//
// Created by guyis on 2019/6/2.
//

#include <util/StringUtil.h>
#include "HashUtil.h"

const unsigned int POLYNOMIAL = 0xEDB88320;

bool Crc32::have_table = false;
unsigned int Crc32::table[256];

void Crc32::make_table() {
    int i, j;
    have_table = true;
    for (i = 0; i < 256; i++)
        for (j = 0, table[i] = i; j < 8; j++)
            table[i] = (table[i] >> 1) ^ ((table[i] & 1) ? POLYNOMIAL : 0);
}

UInt32 Crc32::get(const Byte *buf, int nLength, UInt32 crc) {
    return get((const unsigned char *) buf, nLength, crc);
}

UInt32 Crc32::get(const unsigned char *buf, int nLength, UInt32 u32Crc) {
    if (nLength < 1)
        return 0xffffffff;
    if (!have_table)
        make_table();
    unsigned int crc = u32Crc;
    crc = ~crc;
    for (int i = 0; i < nLength; ++i) {
        crc = table[(crc ^ buf[i]) & 0xff] ^ (crc >> 8);
    }
    return ~crc;
}

Crc32MismatchException::Crc32MismatchException(const std::string &msg, int at) :
        std::runtime_error("")
{
    std::string reason = msg + " At: " + toIntString(at);
    static_cast<std::runtime_error&>(*this) = std::runtime_error(reason);
}
