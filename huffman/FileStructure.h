//
// Created by guyis on 2019/6/1.
//

#ifndef DATA_STRCUT_ASSIGN_FILESTRUCTURE_H
#define DATA_STRCUT_ASSIGN_FILESTRUCTURE_H

#include <vector>
#include "DataType.h"

/**
 * Structure:
 *  proto : HUF
 *  version : 1, 1 bytes
 *  endian : 0, big endian, 1 bytes
 *  partCnt : blocks count
 * Length: 9 bytes
 */
struct HuffmanHeader {
    char proto[3];
    Byte version;
    Byte endian;
    UInt32 partCnt;

    HuffmanHeader(UInt32);

    void writeToBuf(FILE *buf);

    static HuffmanHeader *readFromBuf(FILE *buf);
};

/**
 * Structure:
 *  padCnt 1
 *  blockCnt 4
 * Length: 5 bytes
 */
struct DataPartHeader {
    Byte padCnt;
    UInt32 blockCnt;

    DataPartHeader() : DataPartHeader(0, 0) {}

    DataPartHeader(Byte, UInt32);

    void writeToBuf(FILE *buf);

    static DataPartHeader *readFromBuf(FILE *buf);
};

/**
 * Structure:
 *  header: 8 bits
 *   - seqLength 8 bits: bytes count in seqData
 *   - tokenLength 8 bits: bytes count in dicData
 *  body: seqLength + tokenLength + 1 bytes
 *   - seqData seqLength bytes
 *   - dicData tokenLength + 1 bytes
 *  checksum: crc32 32 bits
 */
class TreeSegment {
public:
    enum SeqTag {
        ST = 0b01, DATA = 0b10, END = 0b00
    };

    typedef std::vector<SeqTag> Seq;
    typedef std::vector<UChar> Tokens;

    static TreeSegment::SeqTag byteToTag(Byte);

    static std::vector<Byte> packSeq(const Seq &);

    static std::vector<Byte> packTokens(const Tokens &);

    static std::vector<Byte> packToBlock(const std::vector<Byte> &tagBytes, const std::vector<Byte> &tokenBytes);

    static BIndex writeRawToBuf(FILE *buf, const Seq &tagSeq, const Tokens &tokens);

    static std::pair<TreeSegment::Seq, TreeSegment::Tokens> readFromBuf(FILE *buf);
};

/**
 * Structure:
 * header: 2 bytes
 *  - length 2 bytes: bytes count in block
 * body: length + 1 bytes
 * checksum: crc32 32 bits
 */
class DataSegment {
public:
    static std::vector<Byte> splitBlocks(const std::vector<Byte> &rawBytes, int &blockCnt);

    static BIndex writeToBuf(FILE *buf, const std::vector<Byte> &blocked);

    static std::vector<Byte> readRawFromBuf(FILE *buf, int blockCnt);
};

/**
 * Utils on data part
 */
class DataPart {
    UChar padCnt;
    std::vector<Byte> pRawData;
    TreeSegment::Seq pSeq;
    TreeSegment::Tokens pTokens;
public:
    DataPart() : padCnt(0b0) {}

    BIndex writeToBuf(FILE *buf);

    bool readFromBuf(FILE *buf);

    /*
     * Getter & Setter
     */

    const std::vector<Byte> &getRawData() const;

    void setRawData(const std::vector<Byte> &rawData);

    const TreeSegment::Seq &getSeq() const;

    void setSeq(const TreeSegment::Seq &seq);

    const TreeSegment::Tokens &getTokens() const;

    void setTokens(const TreeSegment::Tokens &tokens);

    UChar getPadCnt() const;

    void setPadCnt(UChar cnt);
};

/**
 * Utils function
 */

#endif //DATA_STRCUT_ASSIGN_FILESTRUCTURE_H
