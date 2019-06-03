//
// Created by guyis on 2019/6/1.
//

#include <cassert>
#include "Config.h"
#include "DataType.h"

bool Config::isMemBigEndian() {
    union {
        int intVal;
        char byte;
    } memChecker {.intVal = 1};
    return memChecker.byte != 1;
}

void Config::checkEndianConfig() {
#ifdef MEM_LITLLE_ENDIAN
    assert(!isMemBigEndian());
#endif
#ifdef MEM_BIG_ENDIAN
    assert(isMemBigEndian());
#endif
}
