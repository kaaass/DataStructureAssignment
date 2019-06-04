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
    title->setText("��ѡ������ļ���");
    /*
     * ����ѡ��
     */
    vector<string> menuName = {
            compress ? "  ��ѹ���ļ���" : "  ����ѹ�ļ���",
            "  Ŀ���ļ���",
            compress ? "  ��ʼѹ��" : "  ��ʼ��ѹ"
    };
    opMenu = new Menu(-1, 10, menuName, 0);
    /*
     * ��ʼ������
     */
    registerSubWidget(opMenu);
    registerSubWidget(title);
}

/**
 * ��ʼ��
 */
void InputScene::onInit() {
    UI::footer("");
}

std::string InputScene::getTitle() {
    return compress ? "ѹ���ļ�" : "��ѹ�ļ�";
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
                    string path = UI_inputString("������·����");
                    opMenu->setItemText(0, (compress ? "  ��ѹ���ļ���" : "  ����ѹ�ļ���") + path, true);
                    sourcePath = path;
                    UI::footer("�������");
                }
                    break;
                case 1: {
                    string path = UI_inputString("������·����");
                    opMenu->setItemText(1, "  Ŀ���ļ���" + path, true);
                    destPath = path;
                    UI::footer("�������");
                }
                    break;
                case 2:
                    if (compress) {
                        FILE *source = fopen(sourcePath.c_str(), "rb");
                        if (source == nullptr) {
                            UI::footer("����·����������������룡");
                            break;
                        }
                        FILE *dest = fopen(destPath.c_str(), "wb");
                        if (dest == nullptr) {
                            UI::footer("���·����������������룡");
                            break;
                        }
                        UI::footer("����ѹ�������Ժ�...");
                        int64_t stTime = getCurrentTime();
                        compressAndSave(source, dest);
                        fflush(dest);
                        int64_t edTime = getCurrentTime();
                        double cost = (double) (edTime - stTime) / 1000;
                        UI::footer("ѹ���ļ���ɣ���ʱ" + doubleString(cost) + "��");
                    } else {
                        FILE *source = fopen(sourcePath.c_str(), "rb");
                        if (source == nullptr) {
                            UI::footer("����·����������������룡");
                            break;
                        }
                        FILE *dest = fopen(destPath.c_str(), "wb");
                        if (dest == nullptr) {
                            UI::footer("���·����������������룡");
                            break;
                        }
                        UI::footer("���ڽ�ѹ�����Ժ�...");
                        int64_t stTime = getCurrentTime();
                        decompressAndSave(source, dest);
                        fflush(dest);
                        int64_t edTime = getCurrentTime();
                        double cost = (double) (edTime - stTime) / 1000;
                        UI::footer("��ѹ�ļ���ɣ���ʱ" + doubleString(cost) + "��");
                    }
                    UI::getInstance().endScene();
                    break;
            }
        } else if (UI::specKey() == KEY_ESC) {
            // �˳�����
            UI::getInstance().endScene();
        }
    }
}
