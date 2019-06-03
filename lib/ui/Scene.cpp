//
// Created by guyis on 2019/5/29.
//

#include <functional>
#include "UI.h"
#include "Scene.h"

using namespace std;

void BaseScene::registerSubWidget(IWidget &widget) {
    widgets.push_back(ref(widget));
}

void BaseScene::init() {
    onCreate();
    UI::getInstance().BreadCrumb_enter(getTitle());
    UI::getInstance().render();
    onInit();
}

void BaseScene::inLoop() {
    for (auto widget: widgets) {
        // widget.get().inLoop();
    }
    onLoop();
}

void BaseScene::render() {
    for (auto widget: widgets) {
        widget.get().render();
    }
    onRender();
}

BaseScene::BaseScene() {
    widgets.clear();
}

std::string BaseScene::getTitle() {
    return "";
}
