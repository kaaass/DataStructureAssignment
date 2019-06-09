//
// Created by guyis on 2019/5/31.
//

#ifndef DATA_STRCUT_ASSIGN_FOREST_H
#define DATA_STRCUT_ASSIGN_FOREST_H

#include "../bitree.h"

template<typename T>
class forest {
    bitree<T> *tree;
    int treeCnt;

    static bitree<T> *buildTreeFromTrees(std::vector<bitree<T> *>);

    static std::vector<bitree<T> *> splitTrees(bitree<T> *tree);

public:
    forest() : tree(new bitree<T>) {}

    void addTrees(bitree<T> *tr);

    std::vector<bitree<T> *> getTrees();

    ~forest();
};

#endif //DATA_STRCUT_ASSIGN_FOREST_H
