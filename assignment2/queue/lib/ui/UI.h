//
// Created by guyis on 2019/4/8.
//

#ifndef FRESHMAN_PROJ_C_UI_H
#define FRESHMAN_PROJ_C_UI_H

#include "../util/StringUtil.h"
#include "../../../../assignment3/queue/MainScene.h"

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

extern int NOW_SCENE;
extern std::string FOOTER;
extern bool READ_SPEC;
extern int SPEC_KEY;

#define CON_WIDTH 120
#define CON_HEIGHT 30

#define COLOR_DEF 0x70

void UI_mainLoop();

void UI_render();

void UI_getSpecKey();

void UI_setFooterUpdate(std::string);

void UI_startScene(MainScene *scene);

void UI_endScene();

void BreadCrumb_enter(const std::string &name);

void BreadCrumb_exit();

#endif //FRESHMAN_PROJ_C_UI_H
