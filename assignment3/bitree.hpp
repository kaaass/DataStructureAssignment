#include <utility>

//
// Created by guyis on 2019/5/30.
//

#include "bitree.h"
#include <queue>
#include <stack>
#include <sstream>
#include <util/StringUtil.h>

using namespace std;

template<typename T>
bitree<T>::~bitree() {
    // delete data;
    if (father != nullptr) {
        if (this == father->lf)
            father->lf = nullptr;
        if (this == father->rt)
            father->rt = nullptr;
    }
    if (lf != nullptr)
        delete lf;
    if (rt != nullptr)
        delete rt;
}

/**
 * 查找节点
 * @tparam T
 * @return
 */
template<typename T>
vector<bitree<T> *> bitree<T>::find(T &dt) {
    vector<bitree<T> *> ret;
    if (*data == dt) {
        ret.push_back(this);
    }
    if (lf != nullptr) {
        vector<bitree<T> *> sub = lf->find(dt);
        ret.insert(ret.end(), sub.begin(), sub.end());
    }
    if (rt != nullptr) {
        vector<bitree<T> *> sub = rt->find(dt);
        ret.insert(ret.end(), sub.begin(), sub.end());
    }
    return ret;
}

/**
 * 删除子树
 * @tparam T
 */
template<typename T>
void bitree<T>::delSub(bitree<T> *node) {
    if (lf != nullptr) {
        lf->delSub(node);
    }
    if (rt != nullptr) {
        rt->delSub(node);
    }
    if (node == this) {
        delete this;
    }
}

/**
 * 将树转为字符串
 * @tparam T
 * @return
 */
template<typename T>
string bitree<T>::toString() const {
    int cnt;
    string ret, cur;
    if (lf == nullptr && rt == nullptr) return dataString(data);
    cur = dataString(data);
    cnt = cur.size() + 4;
    ret += "( " + cur + " )" + " --- ";
    // First
    if (lf != nullptr)
        ret += lfPad(lf->toString() + "\n", "|", cnt);
    else
        ret += lfPad("nil\n", "|", cnt);
    //  Second
    if (rt != nullptr) {
        ret += '\n';
        for (int i = 0; i < cnt; i++) ret += ' ';
        ret += " --- " + lfPad(rt->toString(), " ", cnt);
    } else {
        ret += "\n";
        for (int i = 0; i < cnt; i++) ret += ' ';
        ret += " --- nil";
    }
    return ret;
}

/**
 * 先根遍历（递归）
 * @tparam T
 * @return
 */
template<typename T>
std::string bitree<T>::dlr(bitree<T> *node) {
    if (node == nullptr) return "";
    return dataString(node->data) + " " + dlr(node->lf) + " " + dlr(node->rt) + " ";
}

/**
 * 中根遍历（递归）
 * @tparam T
 * @return
 */
template<typename T>
std::string bitree<T>::ldr(bitree<T> *node) {
    if (node == nullptr) return "";
    return ldr(node->lf) + " " + dataString(node->data) + " " + ldr(node->rt) + " ";
}

/**
 * 后根遍历（递归）
 * @tparam T
 * @return
 */
template<typename T>
std::string bitree<T>::lrd(bitree<T> *node) {
    if (node == nullptr) return "";
    return lrd(node->lf) + " " + lrd(node->rt) + " " + dataString(node->data) + " ";
}

/**
 * 先根遍历（迭代）
 * @tparam T
 * @return
 */
template<typename T>
std::string bitree<T>::dlrNonRec(bitree<T> *root) {
    string ret;
    stack<bitree<T> *> stk;
    stk.push(root);
    while (!stk.empty()) {
        bitree<T> *node = stk.top();
        stk.pop();
        if (node == nullptr) continue;
        ret += dataString(node->data) + " ";
        stk.push(node->rt);
        stk.push(node->lf);
    }
    return ret;
}

/**
 * 中根遍历（迭代）
 * @tparam T
 * @return
 */
template<typename T>
std::string bitree<T>::ldrNonRec(bitree<T> *root) {
    string ret;
    stack<pair<bitree<T> *, int>> stk;
    stk.push(make_pair(root, 2));
    while (!stk.empty()) {
        pair<bitree<T> *, int> node = stk.top();
        stk.pop();
        if (node.first == nullptr) continue;
        if (node.second == 2) {
            --node.second;
            stk.push(node);
            stk.push(make_pair(node.first->lf, 2));
        } else if (node.second == 1) {
            ret += dataString(node.first->data) + " ";
            stk.push(make_pair(node.first->rt, 2));
        }
    }
    return ret;
}

/**
 * 后根遍历（迭代）
 * @tparam T
 * @return
 */
template<typename T>
std::string bitree<T>::lrdNonRec(bitree<T> *root) {
    string ret;
    stack<pair<bitree<T> *, int>> stk;
    stk.push(make_pair(root, 2));
    while (!stk.empty()) {
        pair<bitree<T> *, int> node = stk.top();
        stk.pop();
        if (node.first == nullptr) continue;
        if (node.second == 2) {
            --node.second;
            stk.push(node);
            stk.push(make_pair(node.first->lf, 2));
        } else if (node.second == 1) {
            --node.second;
            stk.push(node);
            stk.push(make_pair(node.first->rt, 2));
        } else if (node.second == 0)
            ret += dataString(node.first->data) + " ";
    }
    return ret;
}

/**
 * 层次遍历
 * @tparam T
 * @return
 */
template<typename T>
std::string bitree<T>::bfs(bitree<T> *root) {
    string ret;
    queue<bitree<T> *> Q;
    Q.push(root);
    while (!Q.empty()) {
        bitree<T> *node = Q.front();
        Q.pop();
        if (node == nullptr) continue;
        ret += dataString(node->data) + " ";
        Q.push(node->lf);
        Q.push(node->rt);
    }
    return ret;
}

/**
 * 由扩展先根序列建树
 * @tparam T
 * @return
 */
template<typename T>
bitree<T> *bitree<T>::buildFromEptSeq(vector<SeqTag<T>> seq, int &st) {
    auto *ret = new bitree;
    SeqTag<T> curTag;
    if (++st > seq.size() || (curTag = seq[st - 1]).isPlaceHolder())
        return nullptr;
    ret->data = curTag.getData();
    ret->setLeftChild(buildFromEptSeq(seq, st));
    ret->setRightChild(buildFromEptSeq(seq, st));
    return ret;
}

template<typename T>
bitree<T> *bitree<T>::getFather() {
    return father;
}

template<typename T>
std::string bitree<T>::dataString(T *data) {
    ostringstream ss;
    if (data == nullptr)
        return "";
    ss << *data;
    return ss.str();
}

/**
 * 树形打印左侧对齐
 * @tparam T
 * @param lines 子树字符串
 * @param split 竖行分割
 * @param cnt 父节点宽度
 * @return
 */
template<typename T>
std::string bitree<T>::lfPad(std::string tree, std::string split, int cnt) {
    vector<string> lines = splitLines(std::move(tree));
    for (auto it = ++lines.begin(); it != lines.end(); it++) {
        string line;
        for (int i = 0; i < cnt + 1; i++) line += ' ';
        line += split + "   " + *it;
        *it = line;
    }
    return unLines(lines);
}

template<typename T>
void bitree<T>::setLeftChild(bitree<T> *lfChild) {
    lf = lfChild;
    if (lfChild != nullptr) {
        lfChild->father = this;
    }
}

template<typename T>
void bitree<T>::setRightChild(bitree<T> *rtChild) {
    rt = rtChild;
    if (rtChild != nullptr) {
        rtChild->father = this;
    }
}

template<typename T>
bitree<T> *bitree<T>::delFromNode(bitree<T> *root, bitree<T> *node) {
    if (root == node) {
        delete root;
        return nullptr;
    }
    root->delSub(node);
    return root;
}

template<typename T>
bitree<T> *bitree<T>::resolveSub(bitree<T> *tree, std::string seq) {
    if (tree == nullptr)
        return nullptr;
    if (seq.empty())
        return tree;
    if (seq[0] == 'L') {
        return resolveSub(tree->lf, seq.substr(1));
    } else if (seq[0] == 'R') {
        return resolveSub(tree->rt, seq.substr(1));
    }
    return nullptr;
}

template<typename T>
T *bitree<T>::getData() {
    return data;
}

template<typename T>
bitree<T> *bitree<T>::getLeftChild() {
    return lf;
}

template<typename T>
bitree<T> *bitree<T>::getRightChild() {
    return rt;
}

template<typename T>
bool bitree<T>::isLeave() {
    return lf == nullptr && rt == nullptr;
}

template<typename T>
bool SeqTag<T>::isPlaceHolder() {
    return type == PlaceHolder;
}

template<typename T>
T *SeqTag<T>::getData() {
    return data;
}
