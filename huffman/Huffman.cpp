//
// Created by guyis on 2019/6/3.
//

#include "Huffman.h"

bitree<TreeNode>* buildHuffman(const std::map<UChar, int>& charCnt) {
    std::priority_queue<std::pair<int, bitree<TreeNode>*>> forest;

    if (charCnt.empty())
        return nullptr;

    for (auto it: charCnt) {
        auto *tree = new bitree<TreeNode>(new TreeNode(it.first, it.second));
        forest.push(make_pair(-it.second, tree));
    }
    while (forest.size() > 1) {
        auto smallest = forest.top().second;
        forest.pop();
        auto small = forest.top().second;
        forest.pop();
        int weight = smallest->getData()->weight + small->getData()->weight;
        auto *father = new bitree<TreeNode>(new TreeNode(weight));
        father->setLeftChild(smallest);
        father->setRightChild(small);
        forest.push(make_pair(-weight, father));
    }
    return forest.top().second;
}

std::map<UChar, CodePoint> buildDictionary(bitree<TreeNode> *tree) {
    std::map<UChar, CodePoint> map;
    if (tree == nullptr) return map;
    // DFS
    std::stack<std::pair<CodePoint, bitree<TreeNode>*>> stk;
    stk.push(make_pair(CodePoint(), tree));
    while (!stk.empty()) {
        std::pair<CodePoint, bitree<TreeNode>*> cur = stk.top();
        bitree<TreeNode> *curTree = cur.second;
        stk.pop();
        if (curTree->isLeave()) {
            map[curTree->getData()->data] = cur.first;
            continue;
        }
        // 理论上是满树
        CodePoint lfPoint = cur.first;
        stk.push(make_pair(lfPoint.addBitLSB(0), curTree->getLeftChild()));
        CodePoint rtPoint = cur.first;
        stk.push(make_pair(rtPoint.addBitLSB(1), curTree->getRightChild()));
    }
    return map;
}

UChar matchNext(const bitree<TreeNode>*, std::vector<Byte>, int& pos);

std::pair<std::vector<TreeSegment::SeqTag>, std::vector<char>> encodeHuffmanTree(const bitree<TreeNode>*);

bitree<TreeNode>* decodeHuffmanTree(const std::vector<TreeSegment::SeqTag>&, const std::vector<char>&);