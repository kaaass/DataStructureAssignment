//
// Created by guyis on 2019/6/4.
//

#include <ui/UI.h>
#include <ui/widget/Table.h>
#include <ui/widget/Menu.h>
#include <ui/UI_Utils.h>
#include <sys/time.h>
#include <limits>
#include "InputScene.h"
#include "Compress.h"

using namespace std;

void InputScene::onCreate() {
    title = new Label(-1, 2, 50, true);
    title->setText("请选择相关文件！");
    /*
     * 操作选单
     */
    vector<string> menuName = {
            compress ? "  待压缩文件：" : "  待解压文件：",
            "  目标文件：",
            compress ? "  开始压缩" : "  开始解压"
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
void InputScene::onInit() {
    UI::footer("");
}

std::string InputScene::getTitle() {
    return compress ? "压缩文件" : "解压文件";
}

int64_t getCurrentTime() {
    timeval tv{};
    gettimeofday(&tv, nullptr);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

string doubleString(double dbVal) {
    ostringstream out;
    out.precision(2);
    out << dbVal;
    return out.str();
}

void InputScene::onLoop() {
    opMenu->inLoop();
    if (UI::readSpec()) {
        if (UI::specKey() == KEY_ENTER) {
            switch (opMenu->getCur()) {
                case 0: {
                    string path = UI_inputString("请输入路径：");
                    opMenu->setItemText(0, (compress ? "  待压缩文件：" : "  待解压文件：") + path, true);
                    sourcePath = path;
                    UI::footer("设置完毕");
                }
                    break;
                case 1: {
                    string path = UI_inputString("请输入路径：");
                    opMenu->setItemText(1, "  目标文件：" + path, true);
                    destPath = path;
                    UI::footer("设置完毕");
                }
                    break;
                case 2:
                    if (compress) {
                        FILE *source = fopen(sourcePath.c_str(), "rb");
                        if (source == nullptr) {
                            UI::footer("输入路径错误，请检查后再输入！");
                            break;
                        }
                        FILE *dest = fopen(destPath.c_str(), "wb");
                        if (dest == nullptr) {
                            UI::footer("输出路径错误，请检查后再输入！");
                            break;
                        }
                        UI::footer("正在压缩，请稍候...");
                        int64_t stTime = getCurrentTime();
                        compressAndSave(source, dest);
                        fflush(dest);
                        int64_t edTime = getCurrentTime();
                        double cost = (double) (edTime - stTime) / 1000;
                        UI::footer("压缩文件完成，用时" + doubleString(cost) + "秒");
                    } else {
                        FILE *source = fopen(sourcePath.c_str(), "rb");
                        if (source == nullptr) {
                            UI::footer("输入路径错误，请检查后再输入！");
                            break;
                        }
                        FILE *dest = fopen(destPath.c_str(), "wb");
                        if (dest == nullptr) {
                            UI::footer("输出路径错误，请检查后再输入！");
                            break;
                        }
                        UI::footer("正在解压，请稍候...");
                        int64_t stTime = getCurrentTime();
                        decompressAndSave(source, dest);
                        fflush(dest);
                        int64_t edTime = getCurrentTime();
                        double cost = (double) (edTime - stTime) / 1000;
                        UI::footer("解压文件完成，用时" + doubleString(cost) + "秒");
                    }
                    UI::getInstance().endScene();
                    break;
            }
        } else if (UI::specKey() == KEY_ESC) {
            // 退出场景
            UI::getInstance().endScene();
        }
    }
}
