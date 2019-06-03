//
// Created by guyis on 2019/4/8.
//

#ifndef FRESHMAN_PROJ_C_MENU_H
#define FRESHMAN_PROJ_C_MENU_H

#include <string>

typedef struct {
    int x;
    int y;
    int num;
    int cur;
    int line;
    std::vector<std::string> name;
} Menu;

Menu *Menu_create(int x, int y, std::vector<std::string>, int num, int def);

int Menu_render(Menu *menu, int line);

void Menu_inLoop(Menu *);

void Menu_setItemText(Menu *menu, int idx, std::string text, bool reRender);

void Menu_setCur(Menu *, int cur);

void Menu_setCurAndUpdate(Menu *, int cur);

void Menu_destroy(Menu *);

#endif //FRESHMAN_PROJ_C_MENU_H
