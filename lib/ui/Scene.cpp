//
// Created by guyis on 2019/5/29.
//

#include <functional>
#include "UI.h"
#include "Scene.h"

using namespace std;

void BaseScene::registerSubWidget(IWidget *widget) {
    widgets.push_back(widget);
}

void BaseScene::init() {
    onCreate();
    UI::getInstance().BreadCrumb_enter(getTitle());
    UI::getInstance().render();
    onInit();
}

void BaseScene::inLoop() {
    for (auto widget: widgets) {
        if (widget->isEnabled())
            widget->inLoop();
    }
    onLoop();
}

void BaseScene::render() {
    for (auto widget: widgets) {
        widget->render();
    }
    onRender();
}

BaseScene::BaseScene() {
    widgets.clear();
}

std::string BaseScene::getTitle() {
    return "";
}

BaseScene::~BaseScene() {
    for (auto widget: widgets) {
        delete widget;
    }
}
