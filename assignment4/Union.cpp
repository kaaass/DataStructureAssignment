//
// Created by guyis on 2019/6/14.
//

#include "Union.h"

Union::Union(int n) : pre(new int[n + 1]), r(new int[n + 1]) {
    for (int i = 1; i <= n; i++) {
        pre[i] = i;
        r[i] = 0;
    }
}

int Union::find(int s) {
    if (pre[s] == s) {
        return s;
    }
    return pre[s] = find(pre[s]);
}

bool Union::merge(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx == fy) return false;
    if (r[fx] > r[fy]) {
        pre[fy] = fx;
    } else {
        pre[fx] = fy;
        if (r[fx] == r[fy]) r[fy]++;
    }
    return true;
}

bool Union::same(int x, int y) {
    return find(x) == find(y);
}
