//
// Created by guyis on 2019/4/8.
//

#ifndef FRESHMAN_PROJ_C_UI_H
#define FRESHMAN_PROJ_C_UI_H

#include "../util/StringUtil.h"
#include "Scene.h"

#define KEY_SIG 0xE0
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_PGUP 73
#define KEY_RIGHT 77
#define KEY_PGDN 81
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_TAB 9
#define KEY_DEL 83

#define CON_WIDTH 120
#define CON_HEIGHT 30
#define CON_TOP 2

#define COLOR_DEF 0x70

#include <stack>

class UI {
    static UI *instance;

    std::string appName;
    std::string strFooter;
    BaseScene *mainScene;
    bool read_spec;
    int spec_key;
    std::vector<std::string> breadCrumb;
    std::stack<BaseScene *> SCENE_STACK;

    UI() : read_spec(true), mainScene(nullptr) {}

    void init();

    bool runSceneLoop();

    int renderBreadCrumb();

    void renderScene();

    int renderFooter();

    void title(const std::string &name);

public:
    static void start();

    static void reRender();

    static bool readSpec();

    static void setReadSpec(bool read);

    static void setMainScene(BaseScene *scene);

    static int specKey();

    static void setAppName(std::string);

    static void footer(const std::string &);

    static UI &getInstance();

    void mainLoop();

    void render();

    int getSpecKey();

    void setFooterUpdate(const std::string &);

    void startScene(BaseScene *scene);

    void endScene();

    void BreadCrumb_enter(const std::string &name);

    void BreadCrumb_exit();
};

#endif //FRESHMAN_PROJ_C_UI_H
