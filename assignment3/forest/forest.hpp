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
        newNode = curTree == nullptr ? new bitree<T> :
                  new bitree<T>(curTree->getData());
        father = father == nullptr ? ret : father;
        if (father->getLeftChild() == nullptr) {
            father->setLeftChild(newNode);
        } else {
            bitree<T> *rt = father;
            while (rt->getLeftChild() != nullptr) rt = rt->getLeftChild();
            while (rt->getRightChild() != nullptr) rt = rt->getRightChild();
            rt->setRightChild(newNode);
        }
        if (curTree != nullptr && !curTree->isLeave()) {
            Q.push(make_pair(curTree->getLeftChild(), newNode));
            if (curTree->hasRightChild())
                Q.push(make_pair(curTree->getRightChild(), newNode));
        }
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
                if (father->getLeftChild()->getData() == nullptr) {
                    father->setLeftChild(nullptr);
                }
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
std::string forest<T>::dlr() {
    vector<bitree<T> *> trees = getTrees();
    string ret;
    for (auto btree: trees) {
        auto multi = multi_tree<T>::lfSonRtBroTree(btree);
        if (multi != nullptr) {
            ret += multi_tree<T>::dlr(multi) + " ";
        }
    }
    return ret;
}

template<typename T>
std::string forest<T>::lrd() {
    vector<bitree<T> *> trees = getTrees();
    string ret;
    for (auto btree: trees) {
        auto multi = multi_tree<T>::lfSonRtBroTree(btree);
        if (multi != nullptr) {
            ret += multi_tree<T>::lrd(multi) + " ";
        }
    }
    return ret;
}

template<typename T>
std::string forest<T>::bfs() {
    vector<bitree<T> *> trees = getTrees();
    string ret;
    vector<multi_tree<T> *> layer, nextLayer;
    for (auto btree: trees) {
        layer.push_back(multi_tree<T>::lfSonRtBroTree(btree));
    }
    while (!layer.empty()) {
        nextLayer.clear();
        for (auto multi: layer) {
            ret += bitree<T>::dataString(multi->data) + " ";
            for (auto son: multi->sons) {
                nextLayer.push_back(son);
            }
        }
        layer = nextLayer;
    }
    return ret;
}

template<typename T>
std::vector<bitree<T> *> forest<T>::find(T &data) {
    return tree->find(data);
}

template<typename T>
bool forest<T>::delSub(const T &data) {
    vector<bitree<T> *> trees = getTrees();
    vector<bitree<T> *> newTrees;
    queue<bitree<T> *> Q;
    bool flag = false;
    for (bitree<T> *btree: trees) {
        if (*btree->getData() == data)
            continue;
        // Clear
        while (!Q.empty()) Q.pop();
        //
        Q.push(btree);
        while (!Q.empty()) {
            bitree<T> *cur = Q.front();
            Q.pop();
            if (cur == nullptr) continue;
            if (*cur->getData() == data) {
                if (cur->getFather()->getLeftChild() == cur) {
                    cur->getFather()->setLeftChild(cur->getRightChild());
                } else {
                    cur->getFather()->setRightChild(cur->getRightChild());
                }
                flag |= true;
                continue;
            }
            Q.push(cur->getLeftChild());
            Q.push(cur->getRightChild());
        }
        newTrees.push_back(btree);
    }
    tree = buildTreeFromTrees(newTrees);
    return flag;
}

template<typename T>
multi_tree<T> *multi_tree<T>::lfSonRtBroTree(bitree<T> *tree) {
    multi_tree<T> *multi = nullptr;
    queue<pair<bitree<T> *, multi_tree<T> *>> Q; // node, father
    if (tree == nullptr)
        return nullptr;
    Q.push(make_pair(tree, nullptr));
    while (!Q.empty()) {
        bitree<T> *curTree = Q.front().first;
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

template<typename T>
bool multi_tree<T>::delSub(const T &dt) {
    bool flag = false;
    if (dt == *data) {
        sons.clear();
        return true;
    }
    for (auto son: sons) {
        if (dt == *son->data) {
            flag |= true;
            continue;
        }
        flag |= son->delSub(dt);
    }
    return flag;
}

#endif //DATA_STRCUT_ASSIGN_FOREST_HPP
