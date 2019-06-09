//
// Created by guyis on 2019/5/31.
//

#ifndef DATA_STRCUT_ASSIGN_FOREST_H
#define DATA_STRCUT_ASSIGN_FOREST_H

#include "../bitree.h"

template<typename T>
class forest {
    bitree<T> *tree;

    static bitree<T> *buildTreeFromTrees(std::vector<bitree<T> *>);

    static std::vector<bitree<T> *> splitTrees(bitree<T> *tree);

public:
    forest() : tree(new bitree<T>) {}

    void addTrees(bitree<T> *tr);

    std::vector<bitree<T> *> getTrees();

    ~forest();
};

template<typename T>
struct multi_tree {
    T *data;
    vector<multi_tree<T> *> sons;

    static multi_tree *lfSonRtBroTree(bitree<T> *tree);

    multi_tree() : data(nullptr) {}

    multi_tree(T *data) : data(data) {}

    static std::string dlr(multi_tree<T> *);

    static std::string lrd(multi_tree<T> *);
};

#include "forest.hpp"

#endif //DATA_STRCUT_ASSIGN_FOREST_H
