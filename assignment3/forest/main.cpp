#include <iostream>
#include "../bitree.h"
#include "forest.h"

using namespace std;

int main() {
    vector<SeqTag<int> > seq1 = {
            SeqTag<int>(1), SeqTag<int>(2), SeqTag<int>(5), SeqTag<int>(), SeqTag<int>(6), SeqTag<int>(), SeqTag<int>(),
            SeqTag<int>(3), SeqTag<int>(7), SeqTag<int>(), SeqTag<int>(8), SeqTag<int>(), SeqTag<int>(), SeqTag<int>(4),
            SeqTag<int>(), SeqTag<int>(), SeqTag<int>()
    },
    seq2 = {
            SeqTag<int>(1), SeqTag<int>(2), SeqTag<int>(3), SeqTag<int>(), SeqTag<int>(4), SeqTag<int>(), SeqTag<int>(5),
            SeqTag<int>(), SeqTag<int>(), SeqTag<int>(), SeqTag<int>()
    };
    int st1 = 0, st2 = 0;
    bitree<int> *tree1 = bitree<int>::buildFromEptSeq(seq1, st1),
            *tree2 = bitree<int>::buildFromEptSeq(seq2, st2);

    forest<int> pForest;
    pForest.addTrees(tree1);
    cout << pForest.dlr() << endl;
    pForest.addTrees(tree2);
    cout << pForest.dlr() << endl;
    cout << pForest.lrd() << endl;
    cout << pForest.bfs() << endl;
    cout << pForest.delSub(5) << endl;
    cout << pForest.bfs() << endl;
    for (auto btree: pForest.getTrees()) {
        cout << btree->toString() << endl;
    }
    return 0;
}