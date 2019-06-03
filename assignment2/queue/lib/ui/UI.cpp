//
// Created by guyis on 2019/4/8.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include "UI_Utils.h"
#include "UI.h"
#include "scene/MainScene.h"
#include "../../../../assignment3/queue/MainScene.h"

using namespace std;

#define COLOR_FOOTER 0x07

vector<string> BREAD_CRUMB;
stack<int> SCENE_STACK;
std::string FOOTER;
int NOW_SCENE;
bool READ_SPEC;
int SPEC_KEY = 0;

void UI_init() {
    FOOTER = "";
    // 默认场景
    MainScene_init();
}

bool UI_runSceneLoop() {
    switch (NOW_SCENE) {
        case SCENE_MAIN_SCENE:
            MainScene_inLoop();
            break;
        default:
            return false;
    }
    return true;
}

void UI_mainLoop() {
    UI_init();
    UI_render();
    while (true) {
        UI_setCursorVisible(!READ_SPEC);
        UI_getSpecKey();
        if (!UI_runSceneLoop())
            break;
    }
}

int UI_renderBreadCrumb() {
    for(auto cur: BREAD_CRUMB) {
        printf(" %s > ", cur.c_str());
    }
    putchar('\n');
    for (int i = 0; i < CON_WIDTH; i++) putchar('-');
    return 2;
}

int UI_renderScene(int line) {
    switch (NOW_SCENE) {
        case SCENE_MAIN_SCENE:
            return MainScene_render(line);
            // 注册
        default:
            return 0;
    }
}

int UI_renderFooter() {
    UI_setTextColor(COLOR_FOOTER);
    UI_moveCursor((Position) {0, CON_HEIGHT - 1});
    printf("%s", FOOTER.c_str());
    UI_setTextColor(COLOR_DEF);
    Position org = UI_getCursorPos();
    int clearCnt = (int) (CON_WIDTH - UI_stringWidth(FOOTER));
    while (clearCnt--) putchar(' ');
    UI_moveCursor(org);
    return 1;
}

void UI_render() {
    int lineCnt = 0;
    // 重绘
    system("cls");
    // 面包屑
    lineCnt += UI_renderBreadCrumb();
    // 场景
    UI_renderScene(lineCnt);
    // 页脚
    UI_renderFooter();
}

/**
 * 读取特殊键键值
 * @return
 */
void UI_getSpecKey() {
    if (READ_SPEC) {
        SPEC_KEY = 0;
        int key = getch();
        if (key == KEY_SIG) {
            SPEC_KEY = getch();
        } else {
            SPEC_KEY = key;
        }
    }
}

/**
 * 设置页脚
 * @param footer 传入字面字符串常量
 */
void UI_setFooterUpdate(string footer) {
    if (footer == "")
        return;
    FOOTER = footer;
    UI_renderFooter();
}

/**
 * 进入场景（初始化最后调用）
 * @param sceneId
 * @param title
 */
void UI_startScene(MainScene *scene) {
    NOW_SCENE = sceneId;
    BreadCrumb_enter(title);
    SCENE_STACK.push(NOW_SCENE);
    UI_render();
}

/**
 * 退出当前场景
 */
void UI_endScene() {
    BreadCrumb_exit();
    SCENE_STACK.pop();
    NOW_SCENE = SCENE_STACK.top();
    UI_render();
}

void UI_title(const string &name) {
    string title = name + " - Assignment";
    UI_setTitle(name);
}

void BreadCrumb_enter(const string &name) {
    // 更新标题
    UI_title(name);
    // 插入面包屑
    BREAD_CRUMB.push_back(name);
}

void BreadCrumb_exit() {
    BREAD_CRUMB.pop_back();
    UI_title(BREAD_CRUMB.back());
}