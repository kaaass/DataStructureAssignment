#ifndef FRESHMAN_PROJ_C_INVENTORY_H
#define FRESHMAN_PROJ_C_INVENTORY_H

#include <ui/widget/Menu.h>
#include <ui/Scene.h>
#include <ui/widget/TextView.h>
#include "../bitree.h"

#define  SCENE_MAIN_SCENE 1

class MainScene : virtual public BaseScene {
    TextView *dataView;
    Menu *dataMenu;
    bitree<int> *tree;

    enum Column { // 表示当前用户在控制哪一栏
        MENU = 0, RECORD_TABLE
    } curCul;

    void inLoopMenu();

    void inLoopTable();

    void updateTableData();

public:
    std::string getTitle() override;

    void onCreate() override;

    void onInit() override;

    void onLoop() override;
};

#endif //FRESHMAN_PROJ_C_INVENTORY_H
