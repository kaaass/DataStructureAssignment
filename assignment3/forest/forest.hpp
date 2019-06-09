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
        father = father == nullptr ? ret : father;
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
std::vector<bitree<T> *> forest<T>::splitTrees(bitree<T> *tree) {
    std::vector<bitree<T> *> trees;
    queue<pair<bitree<T> *, bitree<T> *>> Q; // node, father
    if (tree == nullptr)
        return trees;
    tree = tree->getLeftChild();
    Q.push(make_pair(tree, nullptr));
    while (!Q.empty()) {
        bitree<T> *curTree = Q.front().first,
                *father = Q.front().second,
                *newNode = nullptr;
        Q.pop();
        if (curTree == nullptr) continue;
        newNode = new bitree<T>(curTree->getData());
        if (father == nullptr) {
            trees.push_back(newNode);
        } else {
            if (!father->hasLeftChild()) { // At lf
                father->setLeftChild(newNode);
            } else { // At rt
                father->setRightChild(newNode);
            }
        }
        Q.push(make_pair(curTree->getLeftChild(), newNode));
        Q.push(make_pair(curTree->getRightChild(), father));
    }
    return trees;
}

template<typename T>
void forest<T>::addTrees(bitree<T> *tr) {
    if (tr == nullptr)
        return;
    vector<bitree<T> *> trees = getTrees();
    trees.push_back(tr);
    tree = buildTreeFromTrees(trees);
}

template<typename T>
std::vector<bitree<T> *> forest<T>::getTrees() {
    return splitTrees(tree);
}

template<typename T>
forest<T>::~forest() {
    delete tree;
}

template<typename T>
multi_tree<T> *multi_tree<T>::lfSonRtBroTree(bitree<T> *tree) {
    multi_tree<T> * multi = nullptr;
    queue<pair<bitree<T> *, multi_tree<T> *>> Q; // node, father
    if (tree == nullptr)
        return nullptr;
    Q.push(make_pair(tree, nullptr));
    while (!Q.empty()) {
        bitree<T> * curTree = Q.front().first;
        multi_tree<T> *father = Q.front().second,
                *newNode = nullptr;
        Q.pop();
        if (curTree == nullptr) continue;
        newNode = new multi_tree<T>(curTree->getData());
        if (father == nullptr) {
            multi = newNode;
        } else {
            father->sons.push_back(newNode);
        }
        Q.push(make_pair(curTree->getLeftChild(), newNode));
        Q.push(make_pair(curTree->getRightChild(), father));
    }
    return multi;
}

template<typename T>
std::string multi_tree<T>::dlr(multi_tree<T> *tree) {
    if (tree == nullptr) return "";
    string ret = bitree<T>::dataString(tree->data);
    for (auto son: tree->sons) {
        ret += " " + dlr(son);
    }
    return ret + " ";
}

template<typename T>
std::string multi_tree<T>::lrd(multi_tree<T> *tree) {
    if (tree == nullptr) return "";
    string ret;
    for (auto son: tree->sons) {
        ret += " " + lrd(son);
    }
    return ret + " " + bitree<T>::dataString(tree->data);
}

#endif //DATA_STRCUT_ASSIGN_FOREST_HPP
