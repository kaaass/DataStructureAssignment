//
// Created by guyis on 2019/6/14.
//

#include "Graph.h"
#include "../Union.h"

#include <queue>
#include <stack>
#include <set>
#include <algorithm>

const int Graph::INF = 0x3f3f3f3f;

void Graph::add(int u, int v, int w) {
    (*this)[u][v] = w;
    (*this)[v][u] = w;
    (*this)(u)[v] = w;
    (*this)(v)[u] = w;
}

int *Graph::operator[](int ind) {
    return &mat[ind * (n + 1)];
}

int Graph::edge(int u, int v) {
    return (*this)(u)[v];
}

vector<int> Graph::bfn(int st, bool *vis) {
    vector<int> ret;
    queue<int> Q;
    Q.push(st);
    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        if (vis[cur]) continue;
        vis[cur] = true;
        for (int i = 1; i <= n; i++) {
            if ((*this)[cur][i] < INF) {
                Q.push(i);
            }
        }
        ret.push_back(cur);
    }
    return ret;
}

vector<int> Graph::dfn(int st, bool *vis) {
    vector<int> ret;
    stack<int> Q;
    Q.push(st);
    while (!Q.empty()) {
        int cur = Q.top();
        Q.pop();
        if (vis[cur]) continue;
        vis[cur] = true;
        for (int i = 1; i <= n; i++) {
            if ((*this)[cur][i] < INF) {
                Q.push(i);
            }
        }
        ret.push_back(cur);
    }
    return ret;
}

vector<int> Graph::bfn() {
    bool vis[n + 1];
    vector<int> ret;
    for (int i = 1; i <= n; i++) vis[i] = false;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vector<int> ts = bfn(i, vis);
            ret.insert(ret.end(), ts.begin(), ts.end());
        }
    }
    return ret;
}

vector<int> Graph::dfn() {
    bool vis[n + 1];
    vector<int> ret;
    for (int i = 1; i <= n; i++) vis[i] = false;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vector<int> ts = dfn(i, vis);
            ret.insert(ret.end(), ts.begin(), ts.end());
        }
    }
    return ret;
}

void Graph::floyd() {
    Graph &G = *this;
    if (path == nullptr)
        path = new int[(n + 1) * (n + 1)];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            path[i * (n + 1) + j] = i != j && G[i][j] < INF ? i : -1;
            G[i][j] = G(i)[j];
        }
    }
    // Run floyd
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (G[i][k] + G[k][j] < G[i][j]) {
                    G[i][j] = G[i][k] + G[k][j];
                    path[i * (n + 1) + j] = path[k * (n + 1) + j];
                }
            }
        }
    }
}

vector<int> Graph::findPath(int u, int v) {
    vector<int> ret;
    Graph &G = *this;
    if (path == nullptr || G[u][v] >= INF)
        return ret;
    // Go along path
    int k = v;
    ret.push_back(v);
    while ((k = path[u * (n + 1) + k]) != u) {
        ret.insert(ret.begin(), k);
    }
    ret.insert(ret.begin(), u);
    return ret;
}

Graph::Graph(int n) : mat(new int[(n + 1) * (n + 1)]), raw(new int[(n + 1) * (n + 1)]), n(n), path(nullptr) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mat[i * (n + 1) + j] = raw[i * (n + 1) + j] = i == j ? 0 : INF;
}

int *Graph::operator()(int ind) {
    return &raw[ind * (n + 1)];
}

int Graph::prim() {
    set<int> U = {1};
    Graph &G = *this;
    int cost = 0;
    int minW, minV;
    while (U.size() < n) {
        minW = INF;
        minV = -1;
        for (auto u0: U) {
            for (int v0 = 1; v0 <= n; v0++) {
                if (U.count(v0) > 0) continue;
                if (G(u0)[v0] < minW) {
                    minW = G(u0)[v0];
                    minV = v0;
                }
            }
        }
        if (minV != -1) {
            U.insert(minV);
            cost += minW;
        }
    }
    return cost;
}

int Graph::kruskal() {
    Graph &G = *this;
    vector<Edge> edges;
    Union un(n);
    // Get edges
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (G(i)[j] < INF) {
                edges.push_back((Edge) {i, j, G(i)[j]});
            }
        }
    }
    // Run
    int cost = 0;
    sort(edges.begin(), edges.end());
    for (auto &edge : edges) {
        if (edge.from != edge.to && un.merge(edge.from, edge.to))
            cost += edge.w;
    }
    return cost;
}

vector<int> Graph::adjacent(int node) {
    Graph &G = *this;
    vector<int> ret;
    for (int i = 1; i <= n; i++) {
        if (i != node && G(node)[i] < INF) {
            ret.push_back(i);
        }
    }
    return ret;
}

Graph::~Graph() {
    delete[] mat;
    delete[] raw;
    if (path != nullptr)
        delete[] path;
}

int Graph::getN() const {
    return n;
}
