//
// Created by guyis on 2019/6/14.
//

#ifndef DATA_STRCUT_ASSIGN_UNION_H
#define DATA_STRCUT_ASSIGN_UNION_H


class Union {

    int *pre, *r;
    int n;
public:
    Union(int n);

    int find(int s);

    bool merge(int x, int y);

    bool same(int x, int y);
};


#endif //DATA_STRCUT_ASSIGN_UNION_H
