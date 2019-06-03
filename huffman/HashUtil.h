#include <utility>

//
// Created by guyis on 2019/6/2.
//

#ifndef DATA_STRCUT_ASSIGN_HASHUTIL_H
#define DATA_STRCUT_ASSIGN_HASHUTIL_H

#include "DataType.h"

class Crc32 {

    static unsigned int table[256];
    static bool have_table;

    static void make_table();

public:
    static UInt32 get(const Byte *buf, int nLength, UInt32 crc = 0x00000000);

    static UInt32 get(const unsigned char *buf, int nLength, UInt32 u32Crc = 0x00000000);
};

class Crc32MismatchException : public std::runtime_error {
public:
    int at;

    Crc32MismatchException(const std::string& msg, int at);
};

#endif //DATA_STRCUT_ASSIGN_HASHUTIL_H
