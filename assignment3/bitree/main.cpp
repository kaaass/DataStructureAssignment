#include <iostream>
#include <ui/UI.h>
#include "MainScene.h"

using namespace std;

int main() {
   /* int st = 0;
    auto sss = splitLines("nil\nA");
    // 1 2 4 . . 5 . . 3 6 . . 7 . .
    vector<SeqTag<int> > seq = {
            SeqTag<int>(1), SeqTag<int>(2), SeqTag<int>(4), SeqTag<int>(), SeqTag<int>(),
            SeqTag<int>(5), SeqTag<int>(), SeqTag<int>(), SeqTag<int>(3), SeqTag<int>(6),
            SeqTag<int>(), SeqTag<int>(), SeqTag<int>(7), SeqTag<int>(), SeqTag<int>()
    };*/
    // 1 2 4 . 6 . . . 3 . 5 . 7 . 8 . .
            /*{
                    SeqTag<int>(1), SeqTag<int>(2), SeqTag<int>(4), SeqTag<int>(), SeqTag<int>(6), SeqTag<int>(), SeqTag<int>(), SeqTag<int>(),
                    SeqTag<int>(3), SeqTag<int>(), SeqTag<int>(5), SeqTag<int>(), SeqTag<int>(7), SeqTag<int>(), SeqTag<int>(8), SeqTag<int>(), SeqTag<int>()
            };*/
    /*bitree<int> *tree = bitree<int>::buildFromEptSeq(seq, st);
    cout << tree->toString() << endl;
    cout << mergeBlanks(bitree<int>::dlr(tree)) << endl;
    cout << mergeBlanks(bitree<int>::ldr(tree)) << endl;
    cout << mergeBlanks(bitree<int>::lrd(tree)) << endl;
    cout << bitree<int>::dlrNonRec(tree) << endl;
    cout << bitree<int>::ldrNonRec(tree) << endl;
    cout << bitree<int>::lrdNonRec(tree) << endl;
    cout << bitree<int>::bfs(tree) << endl;
    int i = 3;
    auto ret = tree->find(i);
    cout << ret.size() << endl;
    cout << ret[0]->toString() << endl;

    cout << bitree<int>::resolveSub(tree, "")->toString() << endl;
    cout << bitree<int>::resolveSub(tree, "R")->toString() << endl;
    cout << bitree<int>::resolveSub(tree, "LR")->toString() << endl;

    bitree<int>::delFromNode(tree, tree);
    cout << tree->toString() << endl;
*/
    UI::setAppName("¶þ²æÊ÷");
    UI::setMainScene(new MainScene);
    UI::start();
    return 0;
}