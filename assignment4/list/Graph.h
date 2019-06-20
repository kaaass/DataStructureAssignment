//
// Created by guyis on 2019/6/14.
//

#ifndef DATA_STRCUT_ASSIGN_GRAPH_H
#define DATA_STRCUT_ASSIGN_GRAPH_H

#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    int w;

    bool operator<(const Edge &e) const {
        return w < e.w;
    }
};

class LGraph {

    vector<vector<Edge>> edges;
public:
    LGraph(int n) : edges(n) {}

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

    vector<int> sort();
};


#endif //DATA_STRCUT_ASSIGN_GRAPH_H
