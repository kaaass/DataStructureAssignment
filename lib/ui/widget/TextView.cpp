//
// Created by guyis on 2019/5/31.
//

#include <ui/UI.h>
#include <iostream>
#include "TextView.h"

using namespace std;

void TextView::render() {
    Position pos(x, y + CON_TOP);
    int mxLine = min(h, (int) contents.size());
    for (int lineNo = curTop; lineNo < h + curTop; lineNo++) {
        UI_moveCursor(pos);
        if (lineNo < contents.size()) {
            string out;
            if (contents[lineNo].size() > curLeft) {
                out = contents[lineNo].substr(curLeft, w);
            }
            cout << out;
            UI_blanks(w - out.size());
        } else {
            UI_blanks(w);
        }
        pos.y++;
    }
}

void TextView::inLoop() {
    if (UI::readSpec()) {
        switch (UI::specKey()) {
            case KEY_UP:
            case KEY_PGUP:
                if (scrollH) {
                    if (curTop <= 0) break;
                    curTop--;
                    render();
                }
                break;
            case KEY_DOWN:
            case KEY_PGDN:
                if (scrollH) {
                    if (curTop + h >= contents.size()) break;
                    curTop++;
                    render();
                }
                break;
            case KEY_LEFT:
                if (scrollV) {
                    if (curLeft <= 0) break;
                    curLeft--;
                    render();
                }
                break;
            case KEY_RIGHT:
                if (scrollV) {
                    if (curLeft + w >= contW) break;
                    curLeft++;
                    render();
                }
                break;
            default:
                break;
        }
    }
}

void TextView::setContents(const string &str) {
    contents = splitLines(str);
    curTop = 0;
    curLeft = 0;
    // Check scroll
    scrollH = contents.size() > h;
    contW = 0;
    for (auto line: contents)
        if (line.size() > contW)
            contW = line.size();
    scrollV = contW > w;
    //
    render();
}
