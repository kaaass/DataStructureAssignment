//
// Created by guyis on 2019/5/16.
//

#ifndef DATA_STRCUT_ASSIGN_QUEUE_H
#define DATA_STRCUT_ASSIGN_QUEUE_H

#include <cstddef>

template<typename T>
class Queue {
    struct QNode {
        T data;
        QNode *next;

        QNode() : next(nullptr) {}
    };

    QNode *head;
    QNode *tail;
    size_t len;
public:
    Queue() : len(0) {
        head = tail = new QNode; // 哨兵结点
    }

    T *top() const;

    void push_back(const T &);

    void pop_front();

    T* get(int ind) const;

    void clear();

    size_t size() const;

    bool empty() const;

    ~Queue();
};

#include "queue.hpp"

#endif //DATA_STRCUT_ASSIGN_QUEUE_H
