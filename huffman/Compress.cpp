//
// Created by guyis on 2019/6/3.
//

#include "Compress.h"

std::unordered_map<UChar, int> countCharBuf(FILE *buf) {
    std::unordered_map<UChar, int> ret;
    UChar ch;
    while (fread(&ch, 1, 1, buf)) {
        ret[ch]++;
    }
    return ret;
}

std::vector<Byte> compressBufWithTree(FILE *buf, bitree<TreeNode> *tree, int &padCnt) {
    auto dict = buildDictionary(tree);
    std::vector<CodePoint> ret;
    UChar ch;
    while (fread(&ch, 1, 1, buf)) {
        ret.push_back(dict[ch]);
    }
    return CodePoint::pack(ret, padCnt);
}

bool compressAndSave(FILE *buf, FILE *writeBuf) {
    int partCnt = 1; // Currently, no multi-file supporting
    // Header
    HuffmanHeader header(partCnt);
    header.writeToBuf(writeBuf);
    // - End of header
    DataPart dataPart;
    // Gene Tree
    auto counts = countCharBuf(buf);
    rewind(buf);
    auto *tree = buildHuffman(counts);
    if (tree == nullptr)
        return false;
    auto treeData = encodeHuffmanTree(tree);
    dataPart.setSeq(treeData.first);
    dataPart.setTokens(treeData.second);
    // Compress & Pack data
    int padCnt;
    auto bytes = compressBufWithTree(buf, tree, padCnt);
    dataPart.setRawData(bytes);
    dataPart.setPadCnt(padCnt);
    dataPart.writeToBuf(writeBuf);
    return true;
}

bool decompressRawAndWrite(FILE *writeBuf, bitree<TreeNode> *tree, const std::vector<Byte> &data, int padCnt) {
    BIndex pos = 0;
    UChar ch;
    while ((pos + padCnt) / 8 < data.size()) {
        if (!matchNext(tree, data, ch, pos))
            return false;
        fwrite(&ch, 1, 1, writeBuf);
    }
    return true;
}

bool decompressAndSave(FILE *buf, FILE *writeBuf) {
    // Header
    HuffmanHeader *header = HuffmanHeader::readFromBuf(buf);
    // - End of header
    DataPart dataPart;
    dataPart.readFromBuf(buf);
    // Rebuild Tree
    auto *tree = decodeHuffmanTree(dataPart.getSeq(), dataPart.getTokens());
    if (tree == nullptr)
        return false;
    // Decompress Data
    return !decompressRawAndWrite(writeBuf, tree, dataPart.getRawData(), dataPart.getPadCnt());
}
