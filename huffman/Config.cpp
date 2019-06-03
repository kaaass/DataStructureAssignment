//
// Created by guyis on 2019/6/1.
//

#include <cassert>
#include "Config.h"
#include "DataType.h"

bool Config::isMemBigEndian() {
    Byte byte = 0b00000001;
    return !byte.bits.b0;
}

void Config::checkEndianConfig() {
#ifdef MEM_LITLLE_ENDIAN
    assert(!isMemBigEndian());
#endif
#ifdef MEM_BIG_ENDIAN
    assert(isMemBigEndian());
#endif
}
