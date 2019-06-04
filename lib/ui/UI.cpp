#include <utility>

//
// Created by guyis on 2019/4/8.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <functional>
#include "UI_Utils.h"
#include "UI.h"

using namespace std;

#define COLOR_FOOTER 0x07

UI *UI::instance = nullptr;

void UI::init() {
    strFooter = "";
    // 默认场景
    UI::startScene(mainScene);
}

bool UI::runSceneLoop() {
    if (SCENE_STACK.empty())
        return false;
    BaseScene* nowScene = SCENE_STACK.top();
    nowScene->inLoop();
    return true;
}

void UI::mainLoop() {
    init();
    render();
    while (true) {
        UI_setCursorVisible(!read_spec);
        getSpecKey();
        if (!runSceneLoop())
            break;
    }
}

int UI::renderBreadCrumb() {
    for (auto cur: breadCrumb) {
        printf(" %s > ", cur.c_str());
    }
    putchar('\n');
    for (int i = 0; i < CON_WIDTH; i++) putchar('-');
    return 2;
}

void UI::renderScene() {
    if (SCENE_STACK.empty())
        return;
    BaseScene* nowScene = SCENE_STACK.top();
    nowScene->render();
}

int UI::renderFooter() {
    UI_setTextColor(COLOR_FOOTER);
    UI_moveCursor((Position) {0, CON_HEIGHT - 1});
    printf("%s", strFooter.c_str());
    UI_setTextColor(COLOR_DEF);
    Position org = UI_getCursorPos();
    int clearCnt = (int) (CON_WIDTH - UI_stringWidth(strFooter));
    while (clearCnt--) putchar(' ');
    UI_moveCursor(org);
    return 1;
}

void UI::render() {
    // 重绘
    system("cls");
    // 面包屑
    renderBreadCrumb();
    // 场景
    renderScene();
    // 页脚
    renderFooter();
}

/**
 * 读取特殊键键值
 * @return
 */
int UI::getSpecKey() {
    if (read_spec) {
        spec_key = 0;
        int key = getch();
        if (key == KEY_SIG) {
            spec_key = getch();
        } else {
            spec_key = key;
        }
    }
    return spec_key;
}

/**
 * 设置页脚
 * @param footerStr 传入字面字符串常量
 */
void UI::setFooterUpdate(const string& footerStr) {
    if (footerStr.empty())
        return;
    this->strFooter = footerStr;
    renderFooter();
}

/**
 * 进入场景（初始化最后调用）
 * @param sceneId
 * @param title
 */
void UI::startScene(BaseScene *scene) {
    scene->init();
    SCENE_STACK.push(scene);
    render();
}

/**
 * 退出当前场景
 */
void UI::endScene() {
    if (SCENE_STACK.size() == 1)
        return;
    BaseScene *nowScene = SCENE_STACK.top();
    BreadCrumb_exit();
    SCENE_STACK.pop();
    delete nowScene;
    render();
}

void UI::title(const string &name) {
    string title = name + " - " + appName;
    UI_setTitle(title);
}

void UI::BreadCrumb_enter(const string &name) {
    // 更新标题
    title(name);
    // 插入面包屑
    breadCrumb.push_back(name);
}

void UI::BreadCrumb_exit() {
    breadCrumb.pop_back();
    title(breadCrumb.back());
}

UI &UI::getInstance() {
    if (UI::instance == nullptr)
        UI::instance = new UI;
    return *UI::instance;
}

void UI::setAppName(std::string name) {
    getInstance().appName = std::move(name);
}

void UI::setReadSpec(bool read) {
    getInstance().read_spec = read;
}

int UI::specKey() {
    return getInstance().spec_key;
}

void UI::reRender() {
    getInstance().render();
}

bool UI::readSpec() {
    return getInstance().read_spec;
}

void UI::footer(const std::string &str) {
    return getInstance().setFooterUpdate(str);
}

void UI::start() {
    if (getInstance().mainScene == nullptr)
        throw invalid_argument("Invoke UI::setMainScene first!");
    getInstance().mainLoop();
}

void UI::setMainScene(BaseScene *scene) {
    getInstance().mainScene = scene;
}
