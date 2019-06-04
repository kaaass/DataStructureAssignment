//
// Created by guyis on 2019/6/1.
//
#include <iostream>
#include <ui/UI.h>
#include "Config.h"
#include "MainScene.h"

using namespace std;

int main() {
    Config::checkEndianConfig();
    UI::setAppName("Huffman—πÀıπ§æﬂ");
    UI::setMainScene(new MainScene);
    UI::start();
    return 0;
}