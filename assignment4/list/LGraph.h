//
// Created by guyis on 2019/6/14.
//

#ifndef DATA_STRCUT_ASSIGN_LGRAPH_H
#define DATA_STRCUT_ASSIGN_LGRAPH_H

#include <vector>
#include <set>
#include "../mat/Graph.h"

using namespace std;

struct Edge {
    int from;
    int to;
    int w;

    Edge(int u, int v, int w): from(u), to(v), w(w) {}
    Edge(int v, int w): from(0), to(v), w(w) {}

    bool operator<(const Edge &e) const {
        return w < e.w;
    }
};

class LGraph {
    int N;

    vector<vector<Edge>> edges;
    set<int> delPoints;
public:
    LGraph(int n) : edges(n + 1), N(n), pMat(nullptr) {}

    void add(int u, int v, int w);

    int edge(int u, int v);

    int insertNode();

    int removeNode(int node);

    int removeEdge(int u, int v);

    vector<int> adjacent(int node);

    vector<int> bfn();

    vector<int> bfn(int st, bool *vis);

    vector<int> dfn();

    vector<int> dfn(int st, bool *vis);

    pair<int, vector<int>> dijkstra(int u, int v);

    void floyd();

    vector<int> findPath(int u, int v);

    int pathLength(int u, int v);

    vector<Edge> sort();

    vector<int> criticalPath();

    Graph * getMat();

private:
    Graph *pMat;
};


#endif //DATA_STRCUT_ASSIGN_LGRAPH_H
