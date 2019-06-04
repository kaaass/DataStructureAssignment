//
// Created by guyis on 2019/6/1.
//

#ifndef DATA_STRCUT_ASSIGN_DATATYPE_H
#define DATA_STRCUT_ASSIGN_DATATYPE_H

#include "Config.h"
#include <vector>
#include <iostream>

struct Bit {
    unsigned char b : 1;

    Bit(unsigned char val) : b(val) {}

    operator unsigned char();

    friend std::ostream & operator<<(std::ostream &, const Bit&);
};

/**
 * Little endian byte
 */
union Byte {
    unsigned char val;

    struct BitPattern {
        unsigned char b0 : 1;
        unsigned char b1 : 1;
        unsigned char b2 : 1;
        unsigned char b3 : 1;
        unsigned char b4 : 1;
        unsigned char b5 : 1;
        unsigned char b6 : 1;
        unsigned char b7 : 1;

        Bit operator[](int ind) const;
    } bits;

    Byte(unsigned char val) : val(val) {}

    Bit operator[](int ind) const;

    FILE * writeToBuf(FILE *) const;

    operator unsigned char() const;

    friend std::ostream & operator<<(std::ostream &, const Byte&);

    Byte() : val(0) {}
};

class UInt32 {
    Byte bytes[4];

    static void uintToBytes(unsigned int, Byte (&bytes)[4]);

    static unsigned int byteToUint(const Byte (&bytes)[4]);
public:
    UInt32() {
        bytes[0] = bytes[1] = bytes[2] = bytes[3] = 0x00;
    }

    UInt32(unsigned int val);

    operator unsigned int();

    UInt32& operator = (unsigned int val);

    std::vector<Byte> toVector();
};

class UInt16 {
    Byte bytes[2];

    static void uintToBytes(unsigned short, Byte (&bytes)[2]);

    static unsigned short byteToUint(const Byte (&bytes)[2]);
public:
    UInt16() {
        bytes[0] = bytes[1] = 0x00;
    }

    UInt16(unsigned short val);

    operator unsigned short();

    UInt16& operator = (unsigned short val);

    std::vector<Byte> toVector();
};

typedef unsigned char UChar;

struct CodePoint {
    std::vector<Byte> bytes;
    int length;

    CodePoint() : length(0), bytes() { bytes.reserve(2); }

    CodePoint(Byte byte, int len) : length(len), bytes() { bytes.reserve(2); bytes.push_back(byte); }

    CodePoint(Byte byte) : CodePoint(byte, 8) {}

    CodePoint &addByteHSB(Byte byte);

    CodePoint &addBitHSB(Bit bit);

    CodePoint &addBitLSB(Bit bit);

    Bit operator[](int ind) const;

    friend std::ostream & operator<<(std::ostream &, const CodePoint&);

    static std::vector<Byte> pack(const std::vector<CodePoint> &points, int &padInt);
};

typedef unsigned long long BIndex;

#endif //DATA_STRCUT_ASSIGN_DATATYPE_H
