//
// Created by guyis on 2019/5/31.
//

#include <ui/UI.h>
#include "Label.h"

void Label::render() {
    int len = std::min((int) UI_stringWidth(content), w);
    int xPos = mid ? (int) (x - len / 2) : x;
    Position pos(xPos, y + CON_TOP);
    UI_moveCursor(pos);
    printf("%s", content.substr(0, len).c_str());
}

void Label::inLoop() {
}

void Label::setText(const std::string &str) {
    content = str;
    render();
}

std::string Label::getText() {
    return content;
}

Label::Label(int x, int y, int w, bool mid) : y(y), w(w), mid(mid) {
    if (x < 0) {
        // 自动居中
        this->x = (int) (CON_WIDTH / 2);
    } else {
        this->x = x;
    }
}
