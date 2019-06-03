//
// Created by guyis on 2019/4/8.
//

#ifndef FRESHMAN_PROJ_C_MENU_H
#define FRESHMAN_PROJ_C_MENU_H

#include <vector>
#include <string>
#include "../UI_Utils.h"
#include "../Widget.h"

class Menu implements IWidget {
    int x;
    int y;
    int num;
    int cur;
    std::vector<std::string> name;

    void renderToggle();
public:
    Menu(int x, int y): Menu(x, y, std::vector<std::string>(), 0) {}

    Menu(int x, int y, std::vector<std::string> name, int def);

    void render() override;

    void inLoop() override;

    int getCur() const;

    void setItemText(int idx, std::string text, bool reRender);

    void setCur(int i);

    void setCurAndUpdate(int cur);

    ~Menu() = default;
};

#endif //FRESHMAN_PROJ_C_MENU_H
