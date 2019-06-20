//
// Created by guyis on 2019/6/14.
//

#include "LGraph.h"

#include <stack>
#include <queue>
#include <cstring>

const int INF = 0x3f3f3f3f;

void LGraph::add(int u, int v, int w) {
    edges[u].push_back(Edge(u, v, w));
}

int LGraph::edge(int u, int v) {
    for (auto e: edges[u]) {
        if (e.to == v) {
            return e.w;
        }
    }
    return -1;
}

int LGraph::insertNode() {
    N++;
    edges.emplace_back();
    return edges.size();
}

int LGraph::removeNode(int node) {
    edges[node].clear();
    delPoints.insert(node);
    N--;
    for (int i = 1; i <= edges.size(); i++)
        if (delPoints.count(i) <= 0)
            removeEdge(i, node);
    return 1;
}

int LGraph::removeEdge(int u, int v) {
    for (auto it = edges[u].begin(); it != edges[u].end();) {
        if (it->to == v) {
            edges[u].erase(it++);
            return 1;
        } else it++;
    }
    return 0;
}

vector<int> LGraph::adjacent(int node) {
    vector<int> ret;
    for (auto e: edges[node]) {
        ret.push_back(e.to);
    }
    return ret;
}

vector<int> LGraph::bfn() {
    bool vis[N + 1];
    vector<int> ret;
    for (int i = 1; i <= N; i++) vis[i] = false;
    for (int i = 1; i <= N; i++) {
        if (delPoints.count(i) <= 0 && !vis[i]) {
            vector<int> ts = bfn(i, vis);
            ret.insert(ret.end(), ts.begin(), ts.end());
        }
    }
    return ret;
}

vector<int> LGraph::dfn() {
    bool vis[N + 1];
    vector<int> ret;
    for (int i = 1; i <= N; i++) vis[i] = false;
    for (int i = 1; i <= N; i++) {
        if (delPoints.count(i) <= 0 && !vis[i]) {
            vector<int> ts = dfn(i, vis);
            ret.insert(ret.end(), ts.begin(), ts.end());
        }
    }
    return ret;
}

vector<int> LGraph::dfn(int st, bool *vis) {
    vector<int> ret;
    stack<int> Q;
    Q.push(st);
    while (!Q.empty()) {
        int cur = Q.top();
        Q.pop();
        if (vis[cur]) continue;
        vis[cur] = true;
        for (auto p: adjacent(cur)) {
            Q.push(p);
        }
        ret.push_back(cur);
    }
    return ret;
}

vector<int> LGraph::bfn(int st, bool *vis) {
    vector<int> ret;
    queue<int> Q;
    Q.push(st);
    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        if (vis[cur]) continue;
        vis[cur] = true;
        for (auto p: adjacent(cur)) {
            Q.push(p);
        }
        ret.push_back(cur);
    }
    return ret;
}

pair<int, vector<int>> LGraph::dijkstra(int u, int v) {
    int dis[N + 1], path[N + 1];
    bool vis[N + 1];

    priority_queue<Edge> Q;
    memset(dis, INF, sizeof(dis));
    memset(path, 0, sizeof(path));
    dis[u] = 0;
    Q.push(Edge(u, 0));
    while (!Q.empty()) {
        Edge t = Q.top();
        Q.pop();
        if (vis[t.to]) continue;
        vis[t.to] = true;
        for (auto e: edges[t.to]) {
            if (dis[e.to] > e.w + t.w) {
                dis[e.to] = e.w + t.w;
                Q.push(Edge(e.to, dis[e.to]));
                path[e.to] = e.from;
            }
        }
    }
    vector<int> ret;
    if (path[v] > 0) {
        int k = v;
        ret.push_back(v);
        while ((k = path[k]) != u) {
            ret.insert(ret.begin(), k);
        }
        ret.insert(ret.begin(), u);
    }
    return make_pair(dis[v], ret);
}

void LGraph::floyd() {
    pMat = getMat();
    pMat->floyd();
}

vector<int> LGraph::findPath(int u, int v) {
    return pMat->findPath(u, v);
}

vector<Edge> LGraph::sort() {
    int degree[N + 1];
    vector<Edge> ret;
    queue<int> Q;

    memset(degree, 0, sizeof(degree));
    for (const auto& E: edges)
        for (auto e: E)
           degree[e.to]++;

    for (int i = 1; i <= N; i++) {
        if (degree[i] == 0) {
            Q.push(i);
        }
        while (!Q.empty()) {
            int cur = Q.front(); Q.pop();
            for (auto e: edges[cur]) {
                ret.push_back(e);
                degree[e.to]--;
                if (degree[e.to] == 0) {
                    Q.push(e.to);
                }
            }
            degree[cur] = -1;
        }
    }
    return ret;
}

vector<int> LGraph::criticalPath() {
    int st, ed;
    int ve[N + 1], vl[N + 1];
    bool isCA[N + 1];
    vector<Edge> topo = sort();
    st = topo[0].from;
    ed = topo[topo.size() - 1].to;

    memset(ve, 0, sizeof(ve));
    ve[st] = 0;
    for (auto e: topo) {
        if (ve[e.to] < ve[e.from] + e.w)
            ve[e.to] = ve[e.from] + e.w;
    }

    memset(vl, INF, sizeof(vl));
    vl[ed] = ve[ed];
    for (auto it = topo.rbegin(); it != topo.rend(); it++) {
        if (vl[it->from] > ve[it->to] - it->w)
            vl[it->from] = ve[it->to] - it->w;
    }

    memset(isCA, 0, sizeof(isCA));
    isCA[ed] = true;
    for (auto e: topo) {
        if (ve[e.from] == vl[e.to] - e.w) {
            isCA[e.from] = true;
        }
    }

    bool vis[N];
    int path[N];
    memset(vis, 0, sizeof(vis));
    memset(path, 0, sizeof(path));
    stack<int> Q;
    Q.push(st);
    while (!Q.empty()) {
        int cur = Q.top();
        Q.pop();
        if (vis[cur]) continue;
        vis[cur] = true;
        for (auto p: adjacent(cur)) {
            if (!isCA[p])
                continue;
            path[p] = cur;
            if (p == ed) break;
            Q.push(p);
        }
    }
    vector<int> ret;
    if (path[ed] == 0)
        return ret;
    int k = ed;
    ret.push_back(ed);
    while ((k = path[k]) != st) {
        ret.insert(ret.begin(), k);
    }
    ret.insert(ret.begin(), st);
    return ret;
}

int LGraph::pathLength(int u, int v) {
    return (*pMat)[u][v];
}

Graph *LGraph::getMat() {
    auto *g = new Graph(N);
    for (const auto& E: edges)
        for (auto e: E)
            g->addSingle(e.from, e.to, e.w);
    return g;
}
