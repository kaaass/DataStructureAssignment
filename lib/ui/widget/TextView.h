//
// Created by guyis on 2019/5/31.
//

#ifndef DATA_STRCUT_ASSIGN_TEXTVIEW_H
#define DATA_STRCUT_ASSIGN_TEXTVIEW_H

#include <vector>
#include <string>
#include "../UI_Utils.h"
#include "../Widget.h"

class TextView implements IWidget {
    int x;
    int y;
    int w;
    int h;
    int curLeft;
    int curTop;
    int contW;
    bool scrollV, scrollH;
    std::vector<std::string> contents;

public:
    TextView(int x, int y, int w, int h) : x(x), y(y), w(w), h(h), curLeft(0), curTop(0) {}

    void render() override;

    void inLoop() override;

    void setContents(const std::string &str);

    ~TextView() = default;
};

#endif //DATA_STRCUT_ASSIGN_TEXTVIEW_H
