//
// Created by guyis on 2019/5/16.
//

#include "List.h"

template<typename T>
T *List<T>::top() const {
    if (len <= 0) return nullptr;
    LNode *node = head->next;
    return &node->data;
}

template<typename T>
void List<T>::insert_back(const T &data) {
    auto *newNode = new LNode;
    newNode->data = data;
    tail->next = newNode;
    tail = newNode;
    cur = newNode;
    len++;
}

template<typename T>
void List<T>::insert_front(const T &data) {
    cur = head;
    insert(data);
}

template<typename T>
void List<T>::insert(const T &data) {
    if (cur == nullptr || cur->next == nullptr) {
        insert_back(data);
        return;
    }
    auto *newNode = new LNode;
    newNode->data = data;
    newNode->next = cur->next;
    cur->next = newNode;
    cur = newNode;
    len++;
}

template<typename T>
void List<T>::remove_front() {
    if (len <= 0)
        return;
    auto *oldNode = head->next;
    head->next = oldNode->next;
    if (cur == oldNode) cur = nullptr;
    delete oldNode;
    len--;
}

template<typename T>
void List<T>::remove() {
    if (len <= 0) return;
    if (cur == nullptr) return;
    auto *oldNode = cur->next;
    if (oldNode == nullptr) return;
    cur->next = oldNode->next;
    cur = oldNode->next;
    delete oldNode;
    len--;
}

template<typename T>
void List<T>::remove_back() {
    if (len <= 0) return;
    auto *it = head;
    while (it->next->next != nullptr)
        it = it->next;
    if (cur == it->next) cur = tail;
    delete it->next;
    it->next = nullptr;
    tail = it;
    len--;
}

template<typename T>
size_t List<T>::size() const {
    return len;
}

template<typename T>
bool List<T>::empty() const {
    return len == 0;
}

template<typename T>
T *List<T>::get() {
    if (cur == nullptr) return nullptr;
    return &cur->data;
}

template<typename T>
T *List<T>::get(int ind) {
    if (len <= 0) return nullptr;
    auto *it = head;
    while (it->next != nullptr && ind-- >= 0)
        it = it->next;
    if (ind >= 0) return nullptr;
    return &it->data;
}

template<typename T>
void List<T>::set(const T &data) {
    if (cur == nullptr) return;
    if (len <= 0) return;
    cur->data = data;
}

template<typename T>
void List<T>::set(const T &data, int ind) {
    if (len <= 0) return;
    auto *it = head;
    while (it->next != nullptr && ind-- >= 0)
        it = it->next;
    if (ind >= 0) return;
    it->data = data;
}

template<typename T>
int List<T>::search(const T &data) {
    auto *it = head;
    int ind = 0;
    while (it->next != nullptr) {
        it = it->next;
        if (it->data == data) {
            cur = it;
            return ind;
        }
        ind++;
    }
    return -1;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, List<T> &list) {
    auto *it = list.head;
    int cnt = 0;
    while (it->next != nullptr) {
        it = it->next;
        out << it->data;
        if (++cnt < list.len)
            out << "->";
    }
    return out;
}

template<typename T>
List<T>::~List() {
    clear();
    delete head;
}

template<typename T>
void List<T>::clear() {
    while (!empty()) {
        remove_back();
    }
}
