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

bool matchNext(bitree<TreeNode> *tree, std::vector<Byte> bytes, UChar &ret, BIndex &pos) {
    UChar ch = 0;
    if (tree == nullptr) return false;
    while (pos / 8 < bytes.size()) {
        Bit bit = bytes[pos / 8][7 - pos % 8];
        pos++;
        if (!bit) {
            tree = tree->getLeftChild();
        } else {
            tree = tree->getRightChild();
        }
        if (tree->isLeave()) {
            ret = tree->getData()->data;
            return true;
        }
    }
    return false;
}

std::pair<TreeSegment::Seq, TreeSegment::Tokens> encodeHuffmanTree(bitree<TreeNode> *tree) {
    TreeSegment::Seq seq;
    TreeSegment::Tokens tokens;
    if (tree != nullptr) {
        std::stack<bitree<TreeNode>*> stk;
        if (!tree->isLeave()) {
            stk.push(tree->getRightChild());
            stk.push(tree->getLeftChild());
        } else stk.push(tree);
        while (!stk.empty()) {
            bitree<TreeNode>* curTree = stk.top();
            stk.pop();
            if (curTree->isLeave()) {
                seq.push_back(TreeSegment::SeqTag::DATA);
                tokens.push_back(curTree->getData()->data);
                continue;
            }
            seq.push_back(TreeSegment::SeqTag::ST);
            stk.push(curTree->getRightChild());
            stk.push(curTree->getLeftChild());
        }
    }
    return make_pair(seq, tokens);
}

bitree<TreeNode>* decodeHuffmanTree(const TreeSegment::Seq& seq, const TreeSegment::Tokens& tokens) {
    auto tree = new bitree<TreeNode>(new TreeNode(0));
    std::stack<int> stk;
    int ind = 0;

    auto curTree = tree;
    stk.push(2);
    for (auto tag: seq) {
        if (stk.empty()) break;
        //
        if (tag == TreeSegment::SeqTag::ST) {
            auto newTree = new bitree<TreeNode>(new TreeNode(0));
            if (stk.top() == 2) {
                curTree->setLeftChild(newTree);
            } else {
                curTree->setRightChild(newTree);
            }
            curTree = newTree;
        } else if (tag == TreeSegment::SeqTag::DATA) {
            auto newTree = new bitree<TreeNode>(new TreeNode(tokens[ind++], 0));
            if (stk.top() == 2) {
                curTree->setLeftChild(newTree);
            } else {
                curTree->setRightChild(newTree);
            }
        }
        --stk.top();
        while (!stk.empty() && stk.top() == 0) {
            stk.pop();
            if (tag == TreeSegment::SeqTag::DATA)
                curTree = curTree->getFather();
        }
        if (tag == TreeSegment::SeqTag::ST) {
            stk.push(2);
        }
    }
    if (!stk.empty()) return nullptr;
    return tree;
}