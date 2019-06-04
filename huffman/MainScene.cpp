#include <ui/UI.h>
#include <ui/widget/Table.h>
#include <ui/widget/Menu.h>
#include <ui/UI_Utils.h>
#include "MainScene.h"
#include "InputScene.h"

using namespace std;

void MainScene::onCreate() {
    title = new Label(-1, 2, 50, true);
    title->setText("欢迎使用Huffman压缩工具！");
    /*
     * 操作选单
     */
    vector<string> menuName = {
            "  压缩文件",
            "  解压文件"
    };
    opMenu = new Menu(-1, 10, menuName, 0);
    /*
     * 初始化数据
     */
    registerSubWidget(opMenu);
    registerSubWidget(title);
}

/**
 * 初始化
 */
void MainScene::onInit() {
    UI::footer("");
}

std::string MainScene::getTitle() {
    return "主页面";
}

void MainScene::onLoop() {
    opMenu->inLoop();
    if (UI::readSpec()) {
        if (UI::specKey() == KEY_ENTER) {
            switch (opMenu->getCur()) {
                case 0:
                    UI::getInstance().startScene(new InputScene(true));
                    break;
                case 1:
                    UI::getInstance().startScene(new InputScene(false));
                    break;
            }
        } else if (UI::specKey() == KEY_ESC) {
            // 退出场景
            UI::getInstance().endScene();
        }
    }
}
