//
// Created by guyis on 2019/6/14.
//

#include "Graph.h"
#include "MainScene.h"
#include <iostream>
#include <util/StringUtil.h>
#include <ui/UI.h>

using namespace std;

int main() {
    UI::setAppName("图：邻接矩阵");
    UI::setMainScene(new MainScene);
    UI::start();
    /*Graph graph(6);
    graph.add(1, 2, 3);
    graph.add(1, 3, 4);
    graph.add(2, 3, 2);
    graph.add(2, 4, 5);
    graph.add(2, 5, 6);
    graph.add(3, 4, 7);
    graph.add(3, 5, 8);
    graph.add(4, 5, 5);
    graph.add(4, 6, 2);
    graph.add(5, 6, 2);

    cout << join(graph.adjacent(3), ", ") << endl;
    cout << graph.node(3, 1) << endl;
    cout << join(graph.dfn(), ", ") << endl;
    cout << join(graph.bfn(), ", ") << endl;
    graph.floyd();
    cout << join(graph.findPath(3, 6), ", ") << endl;
    cout << graph.prim() << endl;
    cout << graph.kruskal() << endl;*/
    return 0;
}
