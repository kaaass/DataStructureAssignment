#include <iostream>
#include "../bitree.h"

using namespace std;

template<typename T>
bitree<T> *buildTreeFromTrees(std::vector<bitree<T> *> trees) {
    auto *ret = new bitree<T>;
    queue<pair<bitree<T> *, bitree<T> *>> Q; // node, father
    for (auto tr : trees)
        Q.push(make_pair(tr, nullptr));
    while (!Q.empty()) {
        bitree<T> *curTree = Q.front().first,
                *father = Q.front().second,
                *newNode;
        if (curTree == nullptr) continue;
        newNode = new bitree<T>(curTree->getData());
        if (father == nullptr) {
            ret->setRightChild(newNode);
        } else {
            bitree<T> *rt = father;
            if (rt->getLeftChild() == nullptr) {
                rt->setLeftChild(newNode);
            } else {
                while (rt->getRightChild() != nullptr) rt = rt->getRightChild();
                rt->setRightChild(newNode);
            }
        }
        Q.push(make_pair(curTree->getLeftChild(), newNode));
        Q.push(make_pair(curTree->getRightChild(), newNode));
    }
    return ret;
}

int main() {
    vector<SeqTag<int> > seq1 = {
            SeqTag<int>(1), SeqTag<int>(2), SeqTag<int>(4), SeqTag<int>(), SeqTag<int>(),
            SeqTag<int>(5), SeqTag<int>(), SeqTag<int>(), SeqTag<int>(3), SeqTag<int>(6),
            SeqTag<int>(), SeqTag<int>(), SeqTag<int>(7), SeqTag<int>(), SeqTag<int>()
    };
    vector<SeqTag<int> > seq2 = {
            SeqTag<int>(8), SeqTag<int>(9), SeqTag<int>(11), SeqTag<int>(), SeqTag<int>(13), SeqTag<int>(), SeqTag<int>(),
            SeqTag<int>(),
            SeqTag<int>(10), SeqTag<int>(), SeqTag<int>(12), SeqTag<int>(), SeqTag<int>(14), SeqTag<int>(), SeqTag<int>(15),
            SeqTag<int>(), SeqTag<int>()
    };
    int st1 = 0, st2 = 0;
    vector<bitree<int> *> trees = {bitree<int>::buildFromEptSeq(seq1, st1), bitree<int>::buildFromEptSeq(seq2, st2)};
    cout << trees[0]->toString() << endl;
    cout << trees[1]->toString() << endl;
    bitree<int> *ret = buildTreeFromTrees(trees);
    cout << ret->toString() << endl;
    /*int cur;

    cout << "****创建单链表****" << endl;
    List<int> list;
    cout << "=>" << list.size() << " 元素" << endl;

    cout << "****在表头插入（以-1结束）****" << endl;
    while (cin >> cur, cur != -1) {
        list.insert_front(cur);
    }
    cout << "=>插入成功" << endl;

    cout << "****在当前节点后插入（以-1结束）****" << endl;
    while (cin >> cur, cur != -1) {
        list.insert(cur);
    }
    cout << "=>插入成功" << endl;

    cout << "****在表尾插入（以-1结束）****" << endl;
    while (cin >> cur, cur != -1) {
        list.insert_back(cur);
    }
    cout << "=>插入成功" << endl;

    cout << "****输出顺序表****" << endl;
    cout << "=>" << list << endl;*/
    return 0;
}