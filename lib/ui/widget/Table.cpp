//
// Created by guyis on 2019/4/11.
//

#include <stdio.h>
#include "Table.h"
#include "util/MemoryUtil.h"
#include "ui/UI.h"
#include "ui/UI_Utils.h"

using namespace std;

#define COLOR_HIGHLIGHT 0x87
#define COLOR_SELECTION 0x07

/**
 * 设置表头信息
 * @param table 表格控件
 * @param columnName 标题
 * @param columnWidth 该列宽度
 * @param columnNum 列数量
 */
void Table::setColumnTitle(vector<string> columnName, int *columnWidth) {
    this->columnName = columnName;
    this->columnNum = columnName.size();
    memcpy(this->columnWidth, columnWidth, sizeof(int) * this->columnNum);
}

int Table::mid(int w, int outW) {
    return (outW - w) / 2;
}

void Table::printBound() {
    for (int i = 0; i < columnNum; i++) {
        putchar('+');
        for (int j = 0; j < columnWidth[i]; j++) putchar('-');
    }
    putchar('+');
}

/**
 *
 * @deprecated 需要更改
 * @param str
 * @param maxLen
 * @return
 */
char *Table::processString(string str, int maxLen) {
    char *buf = const_cast<char *>(str.c_str());
    int curLen;
    // 未超过限制
    if (strlen(buf) <= maxLen) return buf;
    // 超过
    for (int i = 0; i < strlen(buf); i++) {
        curLen = buf[i] > 0x7F ? 2 : 1;
        if (maxLen - curLen - i + 1 <= 3) {
            buf[i] = '.';
            buf[i + 1] = '.';
            buf[i + 2] = '.';
            buf[i + 3] = '\0';
            break;
        }
        if (buf[i] > 0x7F) {
            i++;
            continue;
        }
    }
    return buf;
}

void Table::printLine(vector<string> content, int highlight) {
    for (int i = 0; i < columnNum; i++) {
        char *buf = processString(content[i], columnWidth[i]);
        int len = (int) strlen(buf);
        putchar('|');
        if (highlight == i) UI_setTextColor(COLOR_HIGHLIGHT);
        UI_blanks(mid(len, columnWidth[i]));
        printf("%s", buf);
        UI_blanks(columnWidth[i] - len - mid(len, columnWidth[i]));
        if (highlight == i) UI_setTextColor(COLOR_SELECTION);
    }
    putchar('|');
}

/**
 * 渲染表格
 */
void Table::render() {
    int itemNum = columns.size(),
            usedLine = 4;
    Position pos(x, y + CON_TOP);
    /*
     * 表头
     */
    // 边框
    UI_moveCursor(pos);
    printBound();
    pos.y++;
    // 标题
    UI_moveCursor(pos);
    printLine(columnName, -1);
    pos.y++;
    // 边框
    UI_moveCursor(pos);
    printBound();
    pos.y++; // 边框
    // 打印表内容
    UI_moveCursor(pos);
    for(TableLine data: columns) {
        if (data.id < top) continue;
        if (usedLine >= height) break;
        // 打印一行
        if (data.id == cur) {
            Table::renderToggle(-1);
            pos.y++;
        } else {
            UI_moveCursor(pos);
            printLine(data.content, -1);
            pos.y++;
        }
        usedLine++;
    }
    UI_moveCursor(pos);
    printBound(); // 边框
}

void Table::renderToggle(int orgCur) {
    Position pos(x, y + CON_TOP);
    if (orgCur >= 1) { // orgCur应位于表内
        TableLine data = columns[orgCur - 1];
        pos.y = y + 3 + orgCur - top + CON_TOP;
        UI_moveCursor(pos);
        printLine(data.content, -1);
    }
    UI_setTextColor(COLOR_SELECTION);
    TableLine data = columns[cur - 1];
    pos.y = y + 3 + cur - top + CON_TOP;
    UI_moveCursor(pos);
    printLine(data.content, columnCur);
    UI_setTextColor(COLOR_DEF);
}

bool Table::renderOutOfSight() {
    if (this->cur < this->top) {
        this->top = this->cur;
        render();
    } else if (this->cur - this->top >= this->height - 4) {
        this->top = this->cur - (this->height - 4) + 1;
        render();
    } else {
        return false;
    }
    return true;
}

/**
 * 表格循环间事件
 * @param table 表格控件
 */
void Table::inLoop() {
    int lstCur = this->cur;
    if (this->columns.empty()) // 若无数据则不允许操作
        return;
    if (UI::readSpec()) {
        // 读入按键并处理
        switch (UI::specKey()) {
            /*
             * 行切换
             */
            case KEY_UP:
            case KEY_PGUP:
                if (this->cur == -1) break; // 不渲染选中
                this->cur--;
                if (this->cur < 1)
                    this->cur = this->columns.size();
                break;
            case KEY_DOWN:
            case KEY_PGDN:
                if (this->cur == -1) break; // 不渲染选中
                this->cur++;
                if (this->cur > this->columns.size())
                    this->cur = 1;
                break;
            /*
             * 单元格切换
             */
            case KEY_LEFT:
                if (this->columnCur == -1) break; // 不渲染选中
                this->columnCur--;
                if (this->columnCur < 0)
                    this->columnCur = this->columnNum - 1;
                Table::renderToggle(-1);
                break;
            case KEY_RIGHT:
                if (this->columnCur == -1) break; // 不渲染选中
                this->columnCur++;
                if (this->columnCur >= this->columnNum)
                    this->columnCur = 0;
                Table::renderToggle(-1);
                break;
            default:
                break;
        }
        // 更新绘制
        if (lstCur != this->cur) {
            if (!renderOutOfSight()) {
                Table::renderToggle(lstCur);
            }
        }
    }
}

/**
 * 向表格插入一行数据
 * @param table 表格控件
 * @param line 加入行数据
 */
void Table::pushLine(vector<string> line) {
    TableLine tableLine = {
            .id = (int) this->columns.size() + 1,
            .num = this->columnNum
    };
    tableLine.content = line;
    this->columns.push_back(tableLine);
}

/**
 * 清空表格数据
 * @param table 表格控件
 */
void Table::clear() {
    this->columns.clear();
}

/**
 * 设置当前选择项
 * @param table 表格控件
 * @param cur 当前选择项
 */
void Table::setCur(int cur) {
    this->cur = cur;
}

/**
 * 设置当前选择项并更新
 * @param table 表格控件
 * @param cur 当前选择项
 */
void Table::setCurAndUpdate(int cur) {
    int lstCur = this->cur;
    Table::setCur(cur);
    if (!renderOutOfSight()) {
        Table::renderToggle(lstCur);
    }
}

/**
 * 获得选中单元格的文本
 * @param table 表格控件
 * @return
 */
string Table::getSelection() {
    int selX = this->columnCur, selY = this->cur;
    // 是否允许选中
    if (selX == -1 || selY == -1) return nullptr;
    TableLine data = this->columns[selY];
    return data.content[selX];
}

int Table::getCur() {
    return cur;
}

Table::Table(int x, int y, int w, int h, int def, int colDef) : x(x), y(y), width(w), height(h), cur(def), columnCur(colDef) {
    if (x < 0) {
        // 自动居中
        this->x = (CON_WIDTH - w) / 2;
    } else {
        this->x = x;
    }
    this->top = 1;
}
