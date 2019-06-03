//
// Created by guyis on 2019/4/8.
//

#include <assert.h>
#include <stdio.h>
#include <vector>
#include "Menu.h"
#include "util/MemoryUtil.h"
#include "ui/UI.h"
#include "ui/UI_Utils.h"

using namespace std;

void Menu::renderToggle() {
    Position pos(x + 2, y + CON_TOP);
    Position org = UI_getCursorPos();
    for (int i = 0; i < num; ++i) {
        UI_moveCursor(pos);
        if (cur == i) {
            putchar('*');
        } else {
            putchar(' ');
        }
        pos.y++;
    }
    UI_moveCursor(org);
}

/**
 * 输出菜单内容
 * @param menu
 * @return 占用行数
 */
void Menu::render() {
    Position pos(x, y + CON_TOP);
    for (int i = 0; i < num; ++i) {
        UI_moveCursor(pos);
        printf("[   ] %s\n", name[i].c_str());
        pos.y++;
    }
    renderToggle();
}

/**
 * 菜单的循环间事件
 * @param menu
 */
void Menu::inLoop() {
    if (UI::readSpec()) {
        switch (UI::specKey()) {
            case KEY_UP:
            case KEY_PGUP:
                cur--;
                if (cur < 0)
                    cur = num - 1;
                Menu::renderToggle();
                break;
            case KEY_DOWN:
            case KEY_PGDN:
                cur++;
                if (cur >= num)
                    cur = 0;
                Menu::renderToggle();
                break;
            default:
                break;
        }
    }
}

/**
 * 设置菜单项目文字并更新绘制
 * @param menu
 * @param idx 更改文字的项目
 * @param text 更改的文字
 * @param reRender 是否重绘
 */
void Menu::setItemText(int idx, string text, bool reRender = true) {
    name[idx] = text;
    if (reRender)
        render();
}

/**
 * 设置菜单当前显示的项目
 * @param menu
 * @param i 当前显示项目，0开始，若等于num则无选择项目
 */
void Menu::setCur(int i) {
    cur = i;
}

/**
 * 设置菜单当前显示的项目并直接更新显示
 * @param menu
 * @param cur
 */
void Menu::setCurAndUpdate(int i) {
    Menu::setCur(i);
    UI::reRender();
}

int Menu::getCur() const {
    return cur;
}

Menu::Menu(int x, int y, std::vector<std::string> name, int def) : y(y), name(name), num(name.size()), cur(def) {
    if (x < 0) {
        // 自动居中s
        this->x = (int) ((CON_WIDTH - UI_stringWidth(name[0]) - 6) / 2);
    } else {
        this->x = x;
    }
}
