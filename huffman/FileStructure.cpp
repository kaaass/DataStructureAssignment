//
// Created by guyis on 2019/6/1.
//

#include <basetsd.h>
#include "FileStructure.h"
#include "HashUtil.h"

std::vector<Byte> DataSegment::splitBlocks(const std::vector<Byte> &rawBytes, int &blockCnt) {
    std::vector<Byte> ret;
    int used = 0;
    auto it = rawBytes.begin();
    blockCnt = 0;
    UInt32 checksum;
    UInt16 blockLen;
    while (used < rawBytes.size()) {
        if (rawBytes.size() - used < MAX_DATA_BLOCK_SIZE) {
            blockLen = rawBytes.size() - used;
            auto len = blockLen.toVector();
            ret.insert(ret.end(), len.begin(), len.end());
            ret.insert(ret.end(), it, rawBytes.end());
            checksum = Crc32::get(it.base(), rawBytes.size() - used);
            used = rawBytes.size();
        } else {
            blockLen = MAX_DATA_BLOCK_SIZE;
            auto len = blockLen.toVector();
            ret.insert(ret.end(), len.begin(), len.end());
            ret.insert(ret.end(), it, std::next(it, MAX_DATA_BLOCK_SIZE));
            checksum = Crc32::get(it.base(), MAX_DATA_BLOCK_SIZE);
            std::advance(it, MAX_DATA_BLOCK_SIZE);
            used += MAX_DATA_BLOCK_SIZE;
        }
        auto crc32 = checksum.toVector();
        ret.insert(ret.end(), crc32.begin(), crc32.end());
        blockCnt++;
    }
    return ret;
}

BIndex DataSegment::writeToBuf(FILE *buf, const std::vector<Byte> &blocked) {
    for (auto byte: blocked)
        byte.writeToBuf(buf);
    return blocked.size();
}

std::vector<Byte> DataSegment::readRawFromBuf(FILE *buf, int blockCnt) {
    std::vector<Byte> rawBytes;
    Byte *bBuf = new Byte[MAX_DATA_BLOCK_SIZE];
    int cnt = 0;
    while (blockCnt > 0 && !feof(buf)) {
        UInt16 size;
        fread(&size, 2, 1, buf);
        fread(bBuf, 1, size, buf);
        rawBytes.insert(rawBytes.end(), bBuf, bBuf + size);
        UInt32 checksum;
        fread(&checksum, 4, 1, buf);
        UInt32 calcCrc32 = Crc32::get(bBuf, size);
        if (checksum != calcCrc32) {
            throw Crc32MismatchException("Crc32 Mismatch at blocks.", cnt);
        }
        blockCnt--;
        cnt++;
    }
    delete[] bBuf;
    return rawBytes;
}

HuffmanHeader::HuffmanHeader(UInt32 uPartCnt) {
    proto[0] = 'H';
    proto[1] = 'U';
    proto[2] = 'F';
    version = 0b1;
    // endianFlag[0] = 0xFF;
    // endianFlag[1] = 0xFE;
    endian = 0b1;
    partCnt = uPartCnt;
}

void HuffmanHeader::writeToBuf(FILE *buf) {
    fwrite(proto, 1, 3, buf);
    fwrite(&version, 1, 1, buf);
    fwrite(&endian, 1, 1, buf);
    fwrite(&partCnt, 4, 1, buf);
}

HuffmanHeader *HuffmanHeader::readFromBuf(FILE *buf) {
    auto *ret = new HuffmanHeader(0);
    fread(ret->proto, 1, 3, buf);
    fread(&ret->version, 1, 1, buf);
    fread(&ret->endian, 1, 1, buf);
    fread(&ret->partCnt, 4, 1, buf);
    return ret;
}

std::vector<Byte> TreeSegment::packSeq(const Seq &seq) {
    std::vector<Byte> ret;
    ret.reserve(seq.size() / 4);
    for (int i = 0; i < seq.size(); i++) {
        if (i % 4 == 0)
            ret.emplace_back(0); // Pad with zero
        ret[i / 4].val |= ((unsigned char) seq[i] & 0b11) << 2 * (3 - i % 4);
    }
    return ret;
}

std::vector<Byte> TreeSegment::packTokens(const Tokens &tokens) {
    std::vector<Byte> ret(tokens.begin(), tokens.end());
    return ret;
}

std::vector<Byte> TreeSegment::packToBlock(const std::vector<Byte> &tagBytes, const std::vector<Byte> &tokenBytes) {
    std::vector<Byte> ret;
    Byte seqLength = tagBytes.size(), tokenLength = tokenBytes.size() - 1;
    ret.push_back(seqLength);
    ret.push_back(tokenLength);
    ret.insert(ret.end(), tagBytes.begin(), tagBytes.end());
    ret.insert(ret.end(), tokenBytes.begin(), tokenBytes.end());
    UInt32 checksum = Crc32::get(std::next(ret.begin(), 2).base(), ret.size() - 2);
    auto crc32 = checksum.toVector();
    ret.insert(ret.end(), crc32.begin(), crc32.end());
    return ret;
}

BIndex
TreeSegment::writeRawToBuf(FILE *buf, const Seq &tagSeq, const Tokens &tokens) {
    auto seqBytes = packSeq(tagSeq);
    auto tokenBytes = packTokens(tokens);
    std::vector<Byte> block = packToBlock(seqBytes, tokenBytes);
    for (auto byte: block)
        byte.writeToBuf(buf);
    return block.size();
}

std::pair<TreeSegment::Seq, TreeSegment::Tokens> TreeSegment::readFromBuf(FILE *buf) {
    TreeSegment::Seq seqTags;
    TreeSegment::Tokens tokens;
    Byte *bBuf = new Byte[MAX_TREE_SEG_SIZE];
    unsigned char seqLength, tokenLen;
    unsigned int tokenLength;
    UInt32 calcCrc32;

    fread(&seqLength, 1, 1, buf);
    fread(&tokenLen, 1, 1, buf);
    tokenLength = tokenLen + 1;
    // Read seq
    fread(bBuf, 1, seqLength, buf);
    int used = 0, dtTagCnt = 0;
    while (used < seqLength * 8) {
        TreeSegment::SeqTag tag;
        tag = byteToTag(bBuf[used / 4] >> 2 * (3 - used % 4));
        if (tag == END)
            break;
        else if (tag == DATA)
            dtTagCnt++;
        seqTags.push_back(tag);
        used++;
    }
    calcCrc32 = Crc32::get(bBuf, seqLength);
    // Read token
    fread(bBuf, 1, tokenLength, buf);
    tokens.insert(tokens.end(), bBuf, bBuf + tokenLength);
    calcCrc32 = Crc32::get(bBuf, tokenLength, calcCrc32);
    // Check crc32
    UInt32 checksum;
    fread(&checksum, 4, 1, buf);
    if (checksum != calcCrc32) {
        throw Crc32MismatchException("Crc32 Mismatch at blocks.", -1);
    }
    delete[] bBuf;
    return std::make_pair(seqTags, tokens);
}

TreeSegment::SeqTag TreeSegment::byteToTag(Byte byte) {
    unsigned char val = byte & 0b11;
    if (val == ST)
        return ST;
    if (val == DATA)
        return DATA;
    return END;
}

DataPartHeader::DataPartHeader(Byte pad, UInt32 uBlockCnt) {
    padCnt = pad;
    blockCnt = uBlockCnt;
}

void DataPartHeader::writeToBuf(FILE *buf) {
    fwrite(&padCnt, 1, 1, buf);
    fwrite(&blockCnt, 4, 1, buf);
}

DataPartHeader *DataPartHeader::readFromBuf(FILE *buf) {
    auto *ret = new DataPartHeader;
    fread(&ret->padCnt, 1, 1, buf);
    fread(&ret->blockCnt, 4, 1, buf);
    return ret;
}

const std::vector<Byte> &DataPart::getRawData() const {
    return pRawData;
}

void DataPart::setRawData(const std::vector<Byte> &rawData) {
    DataPart::pRawData = rawData;
}

const TreeSegment::Seq &DataPart::getSeq() const {
    return pSeq;
}

void DataPart::setSeq(const TreeSegment::Seq &seq) {
    DataPart::pSeq = seq;
}

const TreeSegment::Tokens &DataPart::getTokens() const {
    return pTokens;
}

void DataPart::setTokens(const TreeSegment::Tokens &tokens) {
    DataPart::pTokens = tokens;
}

UChar DataPart::getPadCnt() const {
    return padCnt;
}

void DataPart::setPadCnt(UChar cnt) {
    DataPart::padCnt = cnt;
}

BIndex DataPart::writeToBuf(FILE *buf) {
    int blockCnt;
    BIndex size = 5;
    // Blocking data
    auto blocked = DataSegment::splitBlocks(pRawData, blockCnt);
    // Write header
    DataPartHeader dataPartHeader(padCnt, blockCnt);
    dataPartHeader.writeToBuf(buf);
    // Write tree
    size += TreeSegment::writeRawToBuf(buf, pSeq, pTokens);
    // Write blocks
    size += DataSegment::writeToBuf(buf, blocked);
    return size;
}

bool DataPart::readFromBuf(FILE *buf) {
    // Header
    DataPartHeader *header = DataPartHeader::readFromBuf(buf);
    if (header == nullptr) return false;
    padCnt = header->padCnt;
    // Tree Segment
    auto treeInfo = TreeSegment::readFromBuf(buf);
    pSeq = treeInfo.first;
    pTokens = treeInfo.second;
    // Data Segment
    pRawData = DataSegment::readRawFromBuf(buf, header->blockCnt);
    return true;
}
