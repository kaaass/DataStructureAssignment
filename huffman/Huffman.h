//
// Created by guyis on 2019/6/3.
//

#ifndef DATA_STRCUT_ASSIGN_HUFFMAN_H
#define DATA_STRCUT_ASSIGN_HUFFMAN_H

#include "DataType.h"
#include "FileStructure.h"
#include "../assignment3/bitree.h"
#include <unordered_map>

struct TreeNode {
    UChar data;
    int weight;

    TreeNode(UChar data, int weight): data(data), weight(weight) {}
    TreeNode(int weight): TreeNode(0, weight) {}
};

bitree<TreeNode>* buildHuffman(const std::unordered_map<UChar, int>& charCnt);

std::unordered_map<UChar, CodePoint> buildDictionary(bitree<TreeNode> *tree);

bool matchNext(bitree<TreeNode> *tree, std::vector<Byte> bytes, UChar &ret, BIndex &pos);

std::pair<TreeSegment::Seq, TreeSegment::Tokens> encodeHuffmanTree(bitree<TreeNode> *tree);

bitree<TreeNode>* decodeHuffmanTree(const TreeSegment::Seq&, const TreeSegment::Tokens&);

#endif //DATA_STRCUT_ASSIGN_HUFFMAN_H
