//
// Created by guyis on 2019/6/14.
//

#ifndef DATA_STRCUT_ASSIGN_GRAPH_H
#define DATA_STRCUT_ASSIGN_GRAPH_H

#include <vector>

using namespace std;

class Graph {

    int *mat, *raw;
    int n;
    int *path;
public:
    static const int INF;

    Graph(int n);

    void add(int u, int v, int w);

    void addSingle(int u, int v, int w);

    vector<int> adjacent(int node);

    int *operator[](int ind);

    int *operator()(int ind);

    int edge(int u, int v);

    vector<int> bfn();

    vector<int> bfn(int st, bool *vis);

    vector<int> dfn();

    vector<int> dfn(int st, bool *vis);

    void floyd();

    vector<int> findPath(int u, int v);

    int prim();

    int kruskal();

    ~Graph();

    int getN() const;
};


#endif //DATA_STRCUT_ASSIGN_GRAPH_H
