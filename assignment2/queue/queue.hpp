//
// Created by guyis on 2019/5/16.
//

#include "queue.h"

template<typename T>
T *Queue<T>::top() const {
    if (len <= 0) return nullptr;
    QNode *node = head->next;
    return &node->data;
}

template<typename T>
void Queue<T>::push_back(const T &data) {
    auto *newNode = new QNode;
    newNode->data = data;
    tail->next = newNode;
    tail = newNode;
    len++;
}

template<typename T>
void Queue<T>::pop_front() {
    if (len <= 0)
        return;
    auto *oldNode = head->next;
    head->next = oldNode->next;
    delete oldNode;
    len--;
}

template<typename T>
size_t Queue<T>::size() const {
    return len;
}

template<typename T>
bool Queue<T>::empty() const {
    return len == 0;
}

template<typename T>
Queue<T>::~Queue() {
    while (!empty()) {
        pop_front();
    }
    delete head;
}

template<typename T>
T *Queue<T>::get(int ind) const {
    if (len <= 0) return nullptr;
    auto *it = head;
    while (it->next != nullptr && ind-- >= 0)
        it = it->next;
    if (ind >= 0) return nullptr;
    return &it->data;
}

template<typename T>
void Queue<T>::clear() {
    while (!empty())
        pop_front();
}
