//
// Created by guyis on 2019/4/11.
//

#include <stdio.h>
#include "Table.h"
#include "../util/MemoryUtil.h"
#include "UI.h"
#include "UI_Utils.h"

using namespace std;

#define COLOR_HIGHLIGHT 0x87
#define COLOR_SELECTION 0x07

void Table_renderToggle(Table *table, int line, int orgCur);

/**
 * 创建表格控件
 * @param x 左上角x轴坐标
 * @param y 左上角y轴坐标
 * @param w 宽度
 * @param h 高度
 * @param def 默认选中项，若为-1则不渲染
 * @param colDef 默认选中单元格，若为-1则不渲染
 * @return
 */
Table *Table_create(int x, int y, int w, int h, int def, int colDef) {
    Table *table = new Table;
    if (x < 0) {
        // 自动居中
        table->x = (CON_WIDTH - w) / 2;
    } else {
        table->x = x;
    }
    table->y = y;
    table->width = w;
    table->height = h;
    table->cur = def;
    table->columnCur = colDef;
    table->top = 1;
    return table;
}

/**
 * 设置表头信息
 * @param table 表格控件
 * @param columnName 标题
 * @param columnWidth 该列宽度
 * @param columnNum 列数量
 */
void Table_setColumnTitle(Table *table, vector<string> columnName, int *columnWidth, int columnNum) {
    table->columnName = columnName;
    memcpy(table->columnWidth, columnWidth, sizeof(int) * columnNum);
    table->columnNum = columnNum;
}

int mid(int w, int outW) {
    return (outW - w) / 2;
}

void printBound(Table *table) {
    for (int i = 0; i < table->columnNum; i++) {
        putchar('+');
        for (int j = 0; j < table->columnWidth[i]; j++) putchar('-');
    }
    putchar('+');
}

char *processString(string str, int maxLen) {
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

void printLine(Table *table, vector<string> content, int highlight) {
    for (int i = 0; i < table->columnNum; i++) {
        char *buf = processString(content[i], table->columnWidth[i]);
        int len = (int) strlen(buf);
        putchar('|');
        if (highlight == i) UI_setTextColor(COLOR_HIGHLIGHT);
        UI_blanks(mid(len, table->columnWidth[i]));
        printf("%s", buf);
        UI_blanks(table->columnWidth[i] - len - mid(len, table->columnWidth[i]));
        if (highlight == i) UI_setTextColor(COLOR_SELECTION);
    }
    putchar('|');
}

/**
 * 渲染表格
 * @param table 表格控件
 * @param line 内容区开始行
 * @return
 */
int Table_render(Table *table, int line) {
    int itemNum = table->columns.size(),
            usedLine = 4;
    table->line = line;
    Position pos = {.x = table->x, .y = table->y + line};
    /*
     * 表头
     */
    // 边框
    UI_moveCursor(pos);
    printBound(table);
    pos.y++;
    // 标题
    UI_moveCursor(pos);
    printLine(table, table->columnName, -1);
    pos.y++;
    // 边框
    UI_moveCursor(pos);
    printBound(table);
    pos.y++; // 边框
    // 打印表内容
    UI_moveCursor(pos);
    for(TableLine data: table->columns) {
        if (data.id < table->top) continue;
        if (usedLine >= table->height) break;
        // 打印一行
        if (data.id == table->cur) {
            Table_renderToggle(table, line, -1);
            pos.y++;
        } else {
            UI_moveCursor(pos);
            printLine(table, data.content, -1);
            pos.y++;
        }
        usedLine++;
    }
    UI_moveCursor(pos);
    printBound(table); // 边框
    return usedLine;
}

void Table_renderToggle(Table *table, int line, int orgCur) {
    Position pos = {.x = table->x, .y = table->y + line};
    if (orgCur >= 0) { // orgCur应位于表内
        TableLine data = table->columns[orgCur];
        pos.y = table->y + line + 3 + orgCur - table->top;
        UI_moveCursor(pos);
        printLine(table, data.content, -1);
    }
    UI_setTextColor(COLOR_SELECTION);
    TableLine data = table->columns[table->cur - 1];
    pos.y = table->y + line + 3 + table->cur - table->top;
    UI_moveCursor(pos);
    printLine(table, data.content, table->columnCur);
    UI_setTextColor(COLOR_DEF);
}

bool renderOutOfSight(Table *table) {
    if (table->cur < table->top) {
        table->top = table->cur;
        Table_render(table, table->line);
    } else if (table->cur - table->top >= table->height - 4) {
        table->top = table->cur - (table->height - 4) + 1;
        Table_render(table, table->line);
    } else {
        return false;
    }
    return true;
}

/**
 * 表格循环间事件
 * @param table 表格控件
 */
void Table_inLoop(Table *table) {
    int lstCur = table->cur;
    if (table->columns.empty()) // 若无数据则不允许操作
        return;
    if (READ_SPEC) {
        // 读入按键并处理
        switch (SPEC_KEY) {
            /*
             * 行切换
             */
            case KEY_UP:
            case KEY_PGUP:
                if (table->cur == -1) break; // 不渲染选中
                table->cur--;
                if (table->cur < 1)
                    table->cur = table->columns.size();
                break;
            case KEY_DOWN:
            case KEY_PGDN:
                if (table->cur == -1) break; // 不渲染选中
                table->cur++;
                if (table->cur > table->columns.size())
                    table->cur = 1;
                break;
            /*
             * 单元格切换
             */
            case KEY_LEFT:
                if (table->columnCur == -1) break; // 不渲染选中
                table->columnCur--;
                if (table->columnCur < 0)
                    table->columnCur = table->columnNum - 1;
                Table_renderToggle(table, table->line, -1);
                break;
            case KEY_RIGHT:
                if (table->columnCur == -1) break; // 不渲染选中
                table->columnCur++;
                if (table->columnCur >= table->columnNum)
                    table->columnCur = 0;
                Table_renderToggle(table, table->line, -1);
                break;
            default:
                break;
        }
        // 更新绘制
        if (lstCur != table->cur) {
            if (!renderOutOfSight(table)) {
                Table_renderToggle(table, table->line, lstCur);
            }
        }
    }
}

/**
 * 向表格插入一行数据
 * @param table 表格控件
 * @param line 加入行数据
 */
void Table_pushLine(Table *table, vector<string> line) {
    TableLine tableLine = {
            .id = (int) table->columns.size() + 1,
            .num = table->columnNum
    };
    tableLine.content = line;
    table->columns.push_back(tableLine);
}

/**
 * 清空表格数据
 * @param table 表格控件
 */
void Table_clear(Table *table) {
    table->columns.clear();
}

/**
 * 设置当前选择项
 * @param table 表格控件
 * @param cur 当前选择项
 */
void Table_setCur(Table *table, int cur) {
    table->cur = cur;
}

/**
 * 设置当前选择项并更新
 * @param table 表格控件
 * @param cur 当前选择项
 */
void Table_setCurAndUpdate(Table *table, int cur) {
    int lstCur = table->cur;
    Table_setCur(table, cur);
    if (!renderOutOfSight(table)) {
        Table_renderToggle(table, table->line, lstCur);
    }
}

/**
 * 获得选中单元格的文本
 * @param table 表格控件
 * @return
 */
string Table_getSelection(Table *table) {
    int selX = table->columnCur, selY = table->cur;
    // 是否允许选中
    if (selX == -1 || selY == -1) return NULL;
    TableLine data = table->columns[selY];
    return data.content[selX];
}

/**
 * 销毁表格控件
 * @param table 表格控件
 */
void Table_destroy(Table *table) {
    // TODO: 完成销毁表格控件
}