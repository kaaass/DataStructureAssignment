//
// Created by guyis on 2019/6/14.
//

#include <iostream>
#include <util/StringUtil.h>
#include <ui/UI.h>
#include "LGraph.h"
#include "MainScene.h"

using namespace std;

int main() {
    UI::setAppName("图：邻接表");
    UI::setMainScene(new MainScene);
    UI::start();
    /*LGraph graph(7);
    graph.add(1, 2, 3);
    graph.add(1, 4, 6);
    graph.add(1, 3, 2);
    graph.add(2, 5, 4);
    graph.add(2, 4, 2);
    graph.add(3, 4, 1);
    graph.add(3, 6, 3);
    graph.add(4, 5, 1);
    graph.add(5, 7, 3);
    graph.add(6, 7, 4);
    *//*LGraph graph(6);
    graph.add(1, 2, 3);
    graph.add(1, 3, 4);
    graph.add(2, 3, 2);
    graph.add(2, 4, 5);
    graph.add(2, 5, 6);
    graph.add(3, 4, 7);
    graph.add(3, 5, 8);
    graph.add(4, 5, 5);
    graph.add(4, 6, 2);
    graph.add(5, 6, 2);*//*

    cout << join(graph.adjacent(3), ", ") << endl;
    cout << graph.edge(3, 1) << endl;
    cout << join(graph.dfn(), ", ") << endl;
    cout << join(graph.bfn(), ", ") << endl;
    graph.floyd();
    cout << join(graph.findPath(3, 5), ", ") << endl;
    cout << graph.pathLength(3, 5) << endl;
    auto p = graph.dijkstra(3, 5);
    cout << join(p.second, ", ") << endl;
    cout << p.first << endl;
    for (auto e: graph.sort()) {
        cout << e.from << " " << e.to << " " << e.w << endl;
    }
    cout << join(graph.criticalPath(), ", ") << endl;*/
    return 0;
}