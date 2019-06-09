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
            "  ����������     ",
            "  �ȸ��������ݹ飩",
            "  �и��������ݹ飩",
            "  ����������ݹ飩",
            "  �ȸ�������������",
            "  �и�������������",
            "  ���������������",
            "  ��α���",
            "  ���ҽ�㼰�丸��",
            "  ɾ������",
            "  �ͷ���"
    };
    dataMenu = new Menu(4, 5, menuName, 0);
    /*
     * ��ʼ������
     */
    curCul = MENU;
    tree = nullptr;
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
         * ����������
            �ȸ��������ݹ飩
            �и��������ݹ飩
            ����������ݹ飩
            �ȸ�������������
            �и�������������
            ���������������
            ��α���",
            ���ҽ�㼰�丸��
            ɾ������"
         */
        if (UI::specKey() == KEY_ENTER) {
            switch (dataMenu->getCur()) {
                case 0: // ����������
                    {
                        str = UI_inputString("��������չ�ȸ����У�");
                        vector<string> tags = splitStrs(mergeBlanks(str), ' ');
                        vector<SeqTag<int>> seq;
                        for (auto tag: tags) {
                            if (tag == ".")
                                seq.push_back(SeqTag<int>());
                            else
                                seq.push_back(SeqTag<int>(stringToInt(tag)));
                        }
                        int st = 0;
                        tree = bitree<int>::buildFromEptSeq(seq, st);
                        if (st != seq.size()) {
                            tree = nullptr;
                            UI::footer("����ʧ�ܣ���������");
                        } else {
                            UI::footer("�����ɹ�");
                        }
                    }
                    break;
                case 1: // �ȸ��������ݹ飩
                    if (tree == nullptr) {
                        UI::footer("��Ϊ�գ�");
                        break;
                    }
                    UI::footer("�ȸ�������" + mergeBlanks(bitree<int>::dlr(tree)));
                    break;
                case 2: // �и��������ݹ飩
                    if (tree == nullptr) {
                        UI::footer("��Ϊ�գ�");
                        break;
                    }
                    UI::footer("�и�������" + mergeBlanks(bitree<int>::ldr(tree)));
                    break;
                case 3: // ����������ݹ飩
                    if (tree == nullptr) {
                        UI::footer("��Ϊ�գ�");
                        break;
                    }
                    UI::footer("���������" + mergeBlanks(bitree<int>::lrd(tree)));
                    break;
                case 4: // �ȸ�������������
                    if (tree == nullptr) {
                        UI::footer("��Ϊ�գ�");
                        break;
                    }
                    UI::footer("�ȸ�������" + bitree<int>::dlrNonRec(tree));
                    break;
                case 5: // �и�������������
                    if (tree == nullptr) {
                        UI::footer("��Ϊ�գ�");
                        break;
                    }
                    UI::footer("�и�������" + bitree<int>::ldrNonRec(tree));
                    break;
                case 6: // ���������������
                    if (tree == nullptr) {
                        UI::footer("��Ϊ�գ�");
                        break;
                    }
                    UI::footer("���������" + bitree<int>::lrdNonRec(tree));
                    break;
                case 7: // ��α���
                    if (tree == nullptr) {
                        UI::footer("��Ϊ�գ�");
                        break;
                    }
                    UI::footer("��α�����" + bitree<int>::bfs(tree));
                    break;
                case 8: // ���ҽ�㼰�丸��
                    if (tree == nullptr) {
                        UI::footer("��Ϊ�գ�");
                        break;
                    }
                    if (UI_inputInt(&num, "������Ҫ���ҵĽ�㣺")) {
                        string msg;
                        auto ret = tree->find(num);
                        for (auto subTree: ret) {
                            msg += "{ ������� = " + toIntString(*subTree->getData()) + ", ��㸸 = ";
                            if (subTree->getFather() == nullptr) {
                                msg += "��";
                            } else {
                                msg += toIntString(*subTree->getFather()->getData());
                            }
                            msg += " }, ";
                        }
                        if (ret.size() == 0) {
                            UI::footer("δ�ҵ�");
                        } else {
                            UI::footer("���ҵ�" + toIntString(ret.size()) + "�������" + msg);
                        }
                        break;
                    }
                    UI::footer("�����ʽ����");
                    break;
                case 9: // ɾ������
                    if (tree == nullptr) {
                        UI::footer("��Ϊ�գ�");
                        break;
                    }
                    {
                        str = UI_inputString("������ȷ�����ı�־���У�");
                        auto sub = bitree<int>::resolveSub(tree, str);
                        if (sub == nullptr) {
                            UI::footer("�Ҳ����ý�㣡");
                        } else {
                            tree = bitree<int>::delFromNode(tree, sub);
                            UI::footer("ɾ���ɹ���");
                        }
                    }
                    break;
                case 10: // �ͷ���
                    if (tree == nullptr) {
                        UI::footer("��Ϊ�գ�");
                        break;
                    }
                    delete tree;
                    tree = nullptr;
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
    if (tree != nullptr)
        dataView->setContents(tree->toString());
    else
        dataView->setContents("����");
    //UI::reRender();
}
