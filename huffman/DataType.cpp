//
// Created by guyis on 2019/6/1.
//

#include <cassert>
#include "DataType.h"

Bit::operator unsigned char() {
    return b;
}

Bit Byte::BitPattern::operator[](int ind) const {
    assert(ind >= 0 && ind <= 7);
#ifndef MEM_LITLLE_ENDIAN
    ind = 7 - ind;
#endif
    switch (ind) {
        case 0: return b0;
        case 1: return b1;
        case 2: return b2;
        case 3: return b3;
        case 4: return b4;
        case 5: return b5;
        case 6: return b6;
        case 7: return b7;
        default:
            return b0;
    }
}

Bit Byte::operator[](int ind) const {
    return bits[ind];
}

std::ostream &operator<<(std::ostream &out, const Byte &byte) {
    for (int i = 7; i >= 0; i--) {
        out << byte.bits[i];
    }
    return out;
}

FILE *Byte::writeToBuf(FILE *buf) const {
    fwrite(&val, 1, 1, buf);
    return buf;
}

Byte::operator unsigned char() const {
    return val;
}

std::ostream &operator<<(std::ostream &out, const Bit &bit) {
    out << (bit.b != 0);
    return out;
}

CodePoint &CodePoint::addByteHSB(Byte byte) {
    length += 8;
    bytes.push_back(byte);
    return *this;
}

CodePoint &CodePoint::addBitHSB(Bit bit) {
    if (length % 8 == 0)
        bytes.emplace_back(0);
    bytes[length / 8].val |= ((unsigned char) bit & 1) << (length % 8);
    length++;
    return *this;
}

Bit CodePoint::operator[](int ind) const {
    assert(ind >= 0 && ind < length);
    return bytes[ind / 8][ind % 8];
}

std::vector<Byte> CodePoint::pack(const std::vector<CodePoint> &points, int &padInt) {
    std::vector<Byte> bytes;
    int cnt = 0;
    for (auto point: points) {
        for (int i = point.length - 1; i >= 0; i--) {
            if (cnt % 8 == 0)
                bytes.emplace_back(0); // Pad with zero
            bytes[cnt / 8].val |= ((unsigned char) point[i] & 1) << (7 - (cnt % 8));
            cnt++;
        }
    }
    padInt = 8 - (cnt % 8);
    return bytes;
}

std::ostream &operator<<(std::ostream &out, const CodePoint &point) {
    for (int i = point.length - 1; i >= 0; i--) {
        out << point[i];
    }
    return out;
}

UInt32::UInt32(unsigned int val) {
    uintToBytes(val, bytes);
}

UInt32::operator unsigned int() {
    return byteToUint(bytes);
}

UInt32 &UInt32::operator=(unsigned int val) {
    uintToBytes(val, bytes);
    return *this;
}

std::vector<Byte> UInt32::toVector() {
    return std::vector<Byte>(bytes, bytes + 4);
}

void UInt32::uintToBytes(unsigned int uintVal, Byte (&bytes)[4]) {
    for (int i = 0; i < 4; i++) {
        bytes[3 - i] = uintVal;
        uintVal >>= (unsigned) 8;
    }
}

unsigned int UInt32::byteToUint(const Byte (&bytes)[4]) {
    unsigned int ret = 0;
    for (int i = 0; i < 4; i++) {
        ret |= bytes[3 - i] << 8 * i;
    }
    return ret;
}