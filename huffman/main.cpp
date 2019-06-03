//
// Created by guyis on 2019/6/1.
//
#include <iostream>
#include "DataType.h"
#include "FileStructure.h"
#include "HashUtil.h"
#include "Huffman.h"

using namespace std;

int main() {
    Config::checkEndianConfig();
    Byte byte = 0b11010101;
    CodePoint point;
    point.addByteHSB(byte).addByteHSB(byte).addBitHSB(1).addBitHSB(1).addBitHSB(1);
    for (int i = 0; i < 1000; i++) {
        point.addBitHSB(rand() % 2);
    }
    vector<CodePoint> points{point, CodePoint(0b00000000), point};

    TreeSegment::Seq seq = {TreeSegment::SeqTag::DATA, TreeSegment::SeqTag::LF, TreeSegment::SeqTag::DATA,
                                       TreeSegment::SeqTag::DATA, TreeSegment::SeqTag::RT}; // 1001101011

    /*auto bbb =  TreeSegment::packSeq(seq);
    for (auto bbbb : bbb) {
        cout << bbbb;
    }
    cout << endl;*/

    std::map<UChar, int> charCnt;
    charCnt['a'] = 3;
    charCnt['b'] = 4;
    charCnt['c'] = 5;
    charCnt['d'] = 6;
    charCnt['e'] = 10;
    auto *huffman = buildHuffman(charCnt);
    auto mapp = buildDictionary(huffman);
    for (auto it: mapp) {
        cout << it.first << ": " << it.second << endl;
    }
    auto p = encodeHuffmanTree(huffman);
    auto *pp = decodeHuffmanTree(p.first, p.second);
    for (auto it: buildDictionary(pp)) {
        cout << it.first << ": " << it.second << endl;
    }

    int partCnt;

    TreeSegment::Tokens tokens = {'a', 'b', 'c'};
    //
    FILE *file = fopen("test.huf", "wb");

    partCnt = 3;
    HuffmanHeader header(partCnt);
    header.writeToBuf(file);

    for (int i = 0; i < partCnt; i++) {
        DataPart dataPart;
        dataPart.setSeq(seq);
        dataPart.setTokens(tokens);
        int padCnt;
        // Pack data
        auto bytes = CodePoint::pack(points, padCnt);
        dataPart.setRawData(bytes);
        dataPart.setPadCnt(partCnt);
        dataPart.writeToBuf(file);
    }
    fflush(file);

    //

    FILE * f = fopen("test.huf", "rb");
    HuffmanHeader *hd = HuffmanHeader::readFromBuf(f);
    partCnt = hd->partCnt;
    cout << partCnt << endl;

    for (int i = 0; i < partCnt; i++) {
        DataPart dataPart;
        dataPart.readFromBuf(f);
        // cout << (int)dataPart.getPadCnt() << endl;
        // cout << dataPart.getRawData().size() << endl;
    }
    return 0;
}