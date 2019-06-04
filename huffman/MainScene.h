#ifndef FRESHMAN_PROJ_C_INVENTORY_H
#define FRESHMAN_PROJ_C_INVENTORY_H

#include <ui/widget/Menu.h>
#include <ui/Scene.h>
#include <ui/widget/TextView.h>
#include <ui/widget/Label.h>

#define  SCENE_MAIN_SCENE 1

class MainScene : virtual public BaseScene {
    Label *title;
    Menu *opMenu;

public:
    std::string getTitle() override;

    void onCreate() override;

    void onInit() override;

    void onLoop() override;
};

#endif //FRESHMAN_PROJ_C_INVENTORY_H
