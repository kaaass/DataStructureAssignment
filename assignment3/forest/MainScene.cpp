#include <ui/UI.h>
#include <ui/widget/Table.h>
#include <ui/widget/Menu.h>
#include <ui/UI_Utils.h>
#include "MainScene.h"

#define SIDE_WIDTH 35
#define VIEW_WIDTH 80

using namespace std;

void MainScene::onCreate() {
    /*
     * �ұ�������
     */
    UI::setReadSpec(true);
    dataView = new TextView(SIDE_WIDTH, 0, VIEW_WIDTH, 27);
    /*
     * ɸѡ����ѡ��
     */
    vector<string> menuName = {
            "  ����ɭ��       ",
            "  ����һ����",
            "  �ȸ��������ݹ飩",
            "  �и��������ݹ飩",
            "  �ȸ�������������",
            "  �и�������������",
            "  ��α���",
            "  ���ҽ��",
            "  ɾ�����������",
            "  �ͷ�ɭ��"
    };
    dataMenu = new Menu(4, 5, menuName, 0);
    /*
     * ��ʼ������
     */
    curCul = MENU;
    pForest = nullptr;
    registerSubWidget(dataMenu);
    registerSubWidget(dataView);
}

/**
 * ��ʼ��
 */
void MainScene::onInit() {
    UI::footer("");
    updateTableData();
}

std::string MainScene::getTitle() {
    return "��ҳ��";
}

void MainScene::onLoop() {
    /*
     * �л��߼�
     */
    if (UI::readSpec()) {
        if (UI::specKey() == KEY_TAB) {
            // �л�����
            if (curCul == MENU) {
                curCul = RECORD_TABLE;
            } else if (curCul == RECORD_TABLE) {
                curCul = MENU;
            }
            UI::reRender();
            return;
        } else if (UI::specKey() == KEY_ESC) {
            // �˳�����
            UI::getInstance().endScene();
        }
    }
    /*
     * ��������
     */
    if (curCul == MENU) {
        inLoopMenu();
    } else if (curCul == RECORD_TABLE) {
        inLoopTable();
    }
}

/**
 * ������
 */
void MainScene::inLoopTable() {
    dataView->inLoop();
    if (UI::readSpec()) {
        // Nothing
    }
}

/**
 * �˵�����
 */
void MainScene::inLoopMenu() {
    int num, ind, *data;
    string str;
    dataMenu->inLoop();
    if (UI::readSpec()) {
        /*
         * "  ����ɭ��       ",
            "  ����һ����",
            "  �ȸ��������ݹ飩",
            "  �и��������ݹ飩",
            "  �ȸ�������������",
            "  �и�������������",
            "  ��α���",
            "  ���ҽ��",
            "  ɾ�����������",
            "  �ͷ�ɭ��"
         */
        if (UI::specKey() == KEY_ENTER) {
            switch (dataMenu->getCur()) {
                case 0: // ����ɭ��
                    pForest = new forest<int>;
                    UI::footer("����ɭ�ֳɹ���");
                    break;
                case 1: // ����һ����
                    if (pForest == nullptr) {
                        UI::footer("ɭ��Ϊ�գ�");
                        break;
                    }
                    {
                        str = UI_inputString("�������ʾ���������չ�ȸ����У��������ֵܣ���");
                        vector<string> tags = splitStrs(mergeBlanks(str), ' ');
                        vector<SeqTag<int>> seq;
                        for (auto tag: tags) {
                            if (tag == ".")
                                seq.push_back(SeqTag<int>());
                            else
                                seq.push_back(SeqTag<int>(stringToInt(tag)));
                        }
                        int st = 0;
                        bitree<int> *tree = bitree<int>::buildFromEptSeq(seq, st);
                        if (st != seq.size()) {
                            UI::footer("���ʧ�ܣ���������");
                        } else {
                            pForest->addTrees(tree);
                            UI::footer("��ӳɹ�");
                        }
                    }
                    break;
                case 2: // �ȸ��������ݹ飩
                    if (pForest == nullptr) {
                        UI::footer("ɭ��Ϊ�գ�");
                        break;
                    }
                    UI::footer("�ȸ�������" + mergeBlanks(pForest->dlr()));
                    break;
                case 3: // ����������ݹ飩
                    if (pForest == nullptr) {
                        UI::footer("ɭ��Ϊ�գ�");
                        break;
                    }
                    UI::footer("���������" + mergeBlanks(pForest->lrd()));
                    break;
                case 4: // �ȸ�������������
                    if (pForest == nullptr) {
                        UI::footer("ɭ��Ϊ�գ�");
                        break;
                    }
                    UI::footer("�ȸ�������" + pForest->dlrNonRec());
                    break;
                case 5: // ���������������
                    if (pForest == nullptr) {
                        UI::footer("ɭ��Ϊ�գ�");
                        break;
                    }
                    UI::footer("���������" + pForest->lrdNonRec());
                    break;
                case 6: // ��α���
                    if (pForest == nullptr) {
                        UI::footer("ɭ��Ϊ�գ�");
                        break;
                    }
                    UI::footer("��α�����" + pForest->bfs());
                    break;
                case 7: // ���ҽ��
                    if (pForest == nullptr) {
                        UI::footer("ɭ��Ϊ�գ�");
                        break;
                    }
                    if (UI_inputInt(&num, "������Ҫ���ҵĽ�㣺")) {
                        auto ret = pForest->find(num);
                        if (ret.size() == 0) {
                            UI::footer("δ�ҵ�");
                        } else {
                            UI::footer("���ҵ�" + toIntString(ret.size()) + "�������");
                        }
                        break;
                    } else {
                        UI::footer("�����ʽ����");
                    }
                    break;
                case 8: // ɾ�����������
                    if (pForest == nullptr) {
                        UI::footer("ɭ��Ϊ�գ�");
                        break;
                    }
                    {
                        if (UI_inputInt(&num, "������Ҫɾ���Ľ������ݣ�")) {
                            bool ret = pForest->delSub(num);
                            if (!ret) {
                                UI::footer("�Ҳ����ý�㣡");
                            } else {
                                UI::footer("ɾ���ɹ���");
                            }
                        } else {
                            UI::footer("�����ʽ����");
                        }
                    }
                    break;
                case 9: // �ͷ�ɭ��
                    if (pForest == nullptr) {
                        UI::footer("ɭ��Ϊ�գ�");
                        break;
                    }
                    delete pForest;
                    pForest = nullptr;
                    UI::footer("�ͷųɹ���");
                    break;
            }
            updateTableData();
        }
    }
}

/*
 * ���ݸ���
 */

/**
 * ���������������ݱ�
 */
void MainScene::updateTableData() {
    // Database_destroy(purchaseRecords);
    if (pForest != nullptr) {
        auto trees = pForest->getTrees();
        string contents;
        int cnt = 1;
        for (auto tree: trees) {
            contents += "����" + toIntString(cnt++) + "��\n" + tree->toString() + "\n";
        }
        dataView->setContents(contents);
    } else {
        dataView->setContents("ɭ�ֿ�");
    }
    //UI::reRender();
}
