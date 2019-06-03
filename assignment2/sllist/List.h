//
// Created by guyis on 2019/5/16.
//

#ifndef DATA_STRCUT_ASSIGN_LIST_H
#define DATA_STRCUT_ASSIGN_LIST_H

#include <iostream>
#include <cstddef>

template<typename T>
class List {
    struct LNode {
        T data;
        LNode *next;

        LNode() : next(nullptr) {}
    };

    LNode *head;
    LNode *cur;
    LNode *tail;
    size_t len;
public:
    List() : len(0) {
        head = cur = tail = new LNode; // 哨兵结点
    }

    T *top() const;

    void insert_front(const T &);

    void insert(const T &);

    void insert_back(const T &);

    void remove_front();

    void remove();

    void remove_back();

    T* get();

    T* get(int ind);

    void set(const T &);

    void set(const T &, int ind);

    int search(const T &);

    size_t size() const;

    bool empty() const;

    void clear();

    template<class TT>
    friend std::ostream &operator<<(std::ostream &, List<TT> &);

    ~List();
};

#include "List.hpp"

#endif //DATA_STRCUT_ASSIGN_LIST_H
