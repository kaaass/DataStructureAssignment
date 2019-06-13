#include <ui/UI.h>
#include <ui/widget/Table.h>
#include <ui/widget/Menu.h>
#include <ui/UI_Utils.h>
#include "MainScene.h"
#include "InputScene.h"
#include "StatScene.h"

using namespace std;

void MainScene::onCreate() {
    title = new Label(-1, 2, 50, true);
    title->setText("��ӭʹ��Huffmanѹ�����ߣ�");
    /*
     * ����ѡ��
     */
    vector<string> menuName = {
            "  Ƶ��ͳ��",
            "  ѹ���ļ�",
            "  ��ѹ�ļ�"
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
void MainScene::onInit() {
    UI::footer("");
}

std::string MainScene::getTitle() {
    return "��ҳ��";
}

void MainScene::onLoop() {
    opMenu->inLoop();
    if (UI::readSpec()) {
        if (UI::specKey() == KEY_ENTER) {
            switch (opMenu->getCur()) {
                case 0:
                {
                    string path = UI_inputString("������·����");
                    FILE *source = fopen(path.c_str(), "rb");
                    if (source == nullptr) {
                        UI::footer("����·����������������룡");
                        break;
                    }
                    UI::getInstance().startScene(new StatScene(source));
                    break;
                }
                case 1:
                    UI::getInstance().startScene(new InputScene(true));
                    break;
                case 2:
                    UI::getInstance().startScene(new InputScene(false));
                    break;
            }
        } else if (UI::specKey() == KEY_ESC) {
            // �˳�����
            UI::getInstance().endScene();
        }
    }
}
