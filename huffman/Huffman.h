//
// Created by guyis on 2019/6/3.
//

#ifndef DATA_STRCUT_ASSIGN_HUFFMAN_H
#define DATA_STRCUT_ASSIGN_HUFFMAN_H

#include "DataType.h"
#include "FileStructure.h"
#include "../assignment3/bitree.h"
#include <map>

struct TreeNode {
    UChar data;
    int weight;

    TreeNode(UChar data, int weight): data(data), weight(weight) {}
    TreeNode(int weight): TreeNode(0, weight) {}
};

bitree<TreeNode>* buildHuffman(const std::map<UChar, int>& charCnt);

std::map<UChar, CodePoint> buildDictionary(bitree<TreeNode> *tree);

UChar matchNext(const bitree<TreeNode>*, std::vector<Byte>, int& pos);

std::pair<std::vector<TreeSegment::SeqTag>, std::vector<char>> encodeHuffmanTree(const bitree<TreeNode>*);

bitree<TreeNode>* decodeHuffmanTree(const std::vector<TreeSegment::SeqTag>&, const std::vector<char>&);

#endif //DATA_STRCUT_ASSIGN_HUFFMAN_H
