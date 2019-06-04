//
// Created by guyis on 2019/6/4.
//

#ifndef DATA_STRCUT_ASSIGN_INPUTSCENE_H
#define DATA_STRCUT_ASSIGN_INPUTSCENE_H

#include <ui/widget/Menu.h>
#include <ui/Scene.h>
#include <ui/widget/TextView.h>
#include <ui/widget/Label.h>

#define  SCENE_MAIN_SCENE 1

class InputScene : virtual public BaseScene {
    Label *title;
    Menu *opMenu;
    bool compress;

    std::string sourcePath;
    std::string destPath;
public:
    InputScene(bool compress) : compress(compress), BaseScene() {}

    std::string getTitle() override;

    void onCreate() override;

    void onInit() override;

    void onLoop() override;
};

#endif //DATA_STRCUT_ASSIGN_INPUTSCENE_H
