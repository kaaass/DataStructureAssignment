//
// Created by guyis on 2019/4/11.
//

#ifndef FRESHMAN_PROJ_C_TABLE_H
#define FRESHMAN_PROJ_C_TABLE_H

#include "../util/StringUtil.h"
#include <string>
#include <vector>

#define _MAX_TABLE_COLUMN 10
#define DATA_TYPE_TableLine 10 | ID_LIKE

struct TableLine {
    int id;
    std::vector<std::string> content;
    int num;
};

struct Table {
    int x;
    int y;
    int width;
    int height;
    int line;
    std::vector<TableLine> columns;
    std::vector<std::string> columnName;
    int columnWidth[_MAX_TABLE_COLUMN];
    int columnNum;
    int top;
    int cur;
    int columnCur;
};

Table *Table_create(int x, int y, int w, int h, int def, int colDef);

void Table_setColumnTitle(Table *table, std::vector<std::string> columnName, int *columnWidth, int columnNum);

int Table_render(Table *table, int line);

void Table_inLoop(Table *);

void Table_pushLine(Table *table, std::vector<std::string> line);

void Table_clear(Table *table);

void Table_setCur(Table *, int cur);

void Table_setCurAndUpdate(Table *, int cur);

std::string Table_getSelection(Table *);

void Table_destroy(Table *);

#endif //FRESHMAN_PROJ_C_TABLE_H
