//
// Created by guyis on 2019/6/3.
//

#ifndef DATA_STRCUT_ASSIGN_COMPRESS_H
#define DATA_STRCUT_ASSIGN_COMPRESS_H

#include "DataType.h"
#include "Huffman.h"
#include <unordered_map>

/*
 * TODO: Read & Write big file with chunk
 */

std::unordered_map<UChar, int> countCharBuf(FILE *buf, BIndex &fileSize);

std::vector<Byte> compressBufWithTree(FILE *buf, bitree<TreeNode> *tree, int &padCnt, BIndex fileSize);

double compressAndSave(FILE *buf, FILE *writeBuf);

bool decompressRawAndWrite(FILE *writeBuf, bitree<TreeNode> *tree, const std::vector<Byte> &data, int padCnt);

bool decompressAndSave(FILE *buf, FILE *writeBuf);

#endif //DATA_STRCUT_ASSIGN_COMPRESS_H
