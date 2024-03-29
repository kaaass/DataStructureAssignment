//
// Created by guyis on 2019/6/3.
//

#include "Huffman.h"

bitree<TreeNode>* buildHuffman(const std::unordered_map<UChar, int>& charCnt) {
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

std::unordered_map<UChar, CodePoint> buildDictionary(bitree<TreeNode> *tree) {
    std::unordered_map<UChar, CodePoint> map;
    if (tree == nullptr) return map;
    //
    if (tree->isLeave()) {
        CodePoint zero;
        zero.addBitHSB(0);
        map[tree->getData()->data] = zero;
        return map;
    }
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

bool matchNext(bitree<TreeNode> *tree, const vector<Byte> &bytes, UChar &ret, BIndex &pos) {
    if (tree == nullptr) return false;
    if (tree->isLeave()) {
        pos++;
        ret = tree->getData()->data;
        return true;
    }
    while (pos / 8 < bytes.size()) {
        Bit bit = bytes[pos / 8][7 - pos % 8];
        pos++;
        if (!bit) {
            tree = tree->getLeftChild();
        } else {
            tree = tree->getRightChild();
        }
        if (tree == nullptr)
            return false;
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

    if (seq.size() == 1) {
        if (seq[0] == TreeSegment::SeqTag::DATA) {
            tree->getData()->data = tokens[0];
            return tree;
        } else {
            return nullptr;
        }
    }
    auto curTree = tree;
    stk.push(2);
    for (auto tag: seq) {
        if (stk.empty()) break;
        //
        --stk.top();
        if (tag == TreeSegment::SeqTag::ST) {
            auto newTree = new bitree<TreeNode>(new TreeNode(0));
            if (stk.top() == 1) {
                curTree->setLeftChild(newTree);
            } else {
                curTree->setRightChild(newTree);
            }
            curTree = newTree;
            stk.push(2);
            continue;
        } else if (tag == TreeSegment::SeqTag::DATA) {
            auto newTree = new bitree<TreeNode>(new TreeNode(tokens[ind++], 0));
            if (stk.top() == 1) {
                curTree->setLeftChild(newTree);
            } else {
                curTree->setRightChild(newTree);
            }
        }
        while (!stk.empty() && stk.top() == 0) {
            stk.pop();
            curTree = curTree->getFather();
        }
    }
    if (!stk.empty()) return nullptr;
    return tree;
}