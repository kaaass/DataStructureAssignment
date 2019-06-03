//
// Created by guyis on 2019/4/11.
//

#ifndef FRESHMAN_PROJ_C_TABLE_H
#define FRESHMAN_PROJ_C_TABLE_H

#include "../../util/StringUtil.h"
#include "../UI_Utils.h"
#include "../Widget.h"
#include <string>
#include <vector>

#define _MAX_TABLE_COLUMN 10

struct TableLine {
    int id;
    std::vector<std::string> content;
    int num;
};

class Table implements IWidget {
    int x;
    int y;
    int width;
    int height;
    std::vector<TableLine> columns;
    std::vector<std::string> columnName;
    int columnWidth[_MAX_TABLE_COLUMN];
    int columnNum;
    int top;
    int cur;
    int columnCur;

    void renderToggle(int orgCur);

    void printBound();

    void printLine(std::vector<std::string> content, int highlight);

    bool renderOutOfSight();

    static int mid(int w, int outW);

    static char *processString(std::string str, int maxLen);
public:
    Table(int x, int y, int w, int h, int def, int colDef);

    void setColumnTitle(std::vector<std::string> columnName, int *columnWidth);

    void render() override;

    void inLoop() override;

    void pushLine(std::vector<std::string> line);

    void clear();

    void setCur(int cur);

    int getCur();

    void setCurAndUpdate(int cur);

    std::string getSelection();

    ~Table() = default;
};

#endif //FRESHMAN_PROJ_C_TABLE_H
