//
// Created by guyis on 2019/5/31.
//

#ifndef DATA_STRCUT_ASSIGN_FOREST_HPP
#define DATA_STRCUT_ASSIGN_FOREST_HPP

#include "forest.h"

using namespace std;

template<typename T>
bitree<T> *forest<T>::buildTreeFromTrees(std::vector<bitree<T> *> trees) {
    auto *ret = new bitree<T>;
    queue<pair<bitree<T> *, bitree<T> *>> Q; // node, father
    for (auto tr : trees)
        Q.push(make_pair(tr, nullptr));
    while (!Q.empty()) {
        bitree<T> *curTree = Q.front().first,
                *father = Q.front().second,
                *newNode;
        Q.pop();
        if (curTree == nullptr) continue;
        newNode = new bitree<T>(curTree->getData());
        father = father == nullptr ? ret: father;
        if (father->getLeftChild() == nullptr) {
            father->setLeftChild(newNode);
        } else {
            bitree<T> *rt = father;
            while (rt->getLeftChild() != nullptr) rt = rt->getLeftChild();
            while (rt->getRightChild() != nullptr) rt = rt->getRightChild();
            rt->setRightChild(newNode);
        }
        Q.push(make_pair(curTree->getLeftChild(), newNode));
        Q.push(make_pair(curTree->getRightChild(), newNode));
    }
    return ret;
}

template<typename T>
void forest<T>::addTrees(bitree<T> *tr) {
    if (tr == nullptr)
        return;
    vector<bitree<T> *> trees = getTrees();
    trees.push_back(tr);
    tree = buildTreeFromTrees(trees);
    return vector<bitree<T> *>();
}

template<typename T>
std::vector<bitree<T> *> forest<T>::getTrees() {
    // TODO
    return vector<bitree<T> *>();
}

template<typename T>
forest<T>::~forest() {
    delete tree;
}

#endif //DATA_STRCUT_ASSIGN_FOREST_HPP
