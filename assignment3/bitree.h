//
// Created by guyis on 2019/5/30.
//

#ifndef DATA_STRCUT_ASSIGN_BITREE_H
#define DATA_STRCUT_ASSIGN_BITREE_H

#include <vector>
#include <string>

template<typename T>
class SeqTag {
public:
    enum TagType {
        Node, PlaceHolder
    };

    SeqTag() : data(nullptr), type(PlaceHolder) {}

    SeqTag(T dt) : type(Node) { data = new T; *data = dt; }

    SeqTag(T &dt) : data(&dt), type(Node) {}

    bool isPlaceHolder();

    T * getData();
private:
    T *data;
    TagType type;
};

template<typename T>
class bitree {
    bitree *father;
    bitree *lf;
    bitree *rt;

    T *data;

    static std::string dataString(T *);

    static std::string lfPad(std::string, std::string, int cnt);
public:
    bitree() : father(nullptr), lf(nullptr), rt(nullptr), data(nullptr) {}

    bitree(T *data) : father(nullptr), lf(nullptr), rt(nullptr), data(data) {}

    bitree<T> *getFather();

    std::vector<bitree<T> *> find(T &);

    void delSub(bitree<T> *);

    std::string toString() const;

    void setLeftChild(bitree<T> *);

    bitree<T> *getLeftChild();

    bool hasLeftChild();

    void setRightChild(bitree<T> *);

    bitree<T> *getRightChild();

    bool hasRightChild();

    T* getData();

    bool isLeave();

    static std::string dlr(bitree<T> *);

    static std::string ldr(bitree<T> *);

    static std::string lrd(bitree<T> *);

    static std::string dlrNonRec(bitree<T> *);

    static std::string ldrNonRec(bitree<T> *);

    static std::string lrdNonRec(bitree<T> *);

    static std::string bfs(bitree<T> *);

    static bitree<T> *buildFromEptSeq(std::vector<SeqTag<T>>, int &st);

    static bitree<T> *delFromNode(bitree<T> *, bitree<T> *);

    static bitree<T> *resolveSub(bitree<T> *, std::string seq);

    ~bitree();
};

#include "bitree.hpp"

#endif //DATA_STRCUT_ASSIGN_BITREE_H
