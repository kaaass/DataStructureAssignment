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
     * �ұ������ڽӾ���
     */
    UI::setReadSpec(true);
    dataView = new TextView(SIDE_WIDTH, 0, VIEW_WIDTH, 27);
    /*
     * ɸѡ����ѡ��
     */
    vector<string> menuName = {
            "  ���ļ�����ͼ",
            "  ��Ȩֵ",
            "  �ڽӶ���",
            "  DFN",
            "  BFN",
            "  Floyd",
            "  Prim",
            "  Kruskal",
            "  �ͷ�ͼ"
    };
    dataMenu = new Menu(4, 5, menuName, 0);
    /*
     * ��ʼ������
     */
    curCul = MENU;
    graph = nullptr;
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
         * "  ���ļ�����ͼ",
            "  ��Ȩֵ",
            "  �ڽӶ���",
            "  DFN",
            "  BFN",
            "  Floyd",
            "  Prim",
            "  Kruskal",
            "  �ͷ�ͼ"
         */
        if (UI::specKey() == KEY_ENTER) {
            switch (dataMenu->getCur()) {
                case 0: // ���ļ�����ͼ
                    {
                        str = UI_inputString("�������ļ�����");
                        FILE *file = fopen(str.c_str(), "r");
                        if (file == nullptr) {
                            UI::footer("�ļ���ʧ�ܣ�");
                            break;
                        }
                        int n, m, u, v, w;
                        fscanf(file, "%d%d", &n, &m);
                        graph = new Graph(n);
                        while (m--) {
                            fscanf(file, "%d%d%d", &u, &v, &w);
                            graph->add(u, v, w);
                        }
                        UI::footer("�����ɹ�");
                    }
                    break;
                case 1: // ��Ȩֵ
                {
                    if (graph == nullptr) {
                        UI::footer("ͼΪ�գ�");
                        break;
                    }
                    int u, v, w;
                    if (UI_inputInt(&num, "��������ʼ�㣺")) {
                        u = num;
                        if (UI_inputInt(&num, "�������յ㣺")) {
                            v = num;
                            w = graph->node(u, v);
                            if (w < Graph::INF) {
                                UI::footer("��Ȩֵ��" + toString(w));
                            } else {
                                UI::footer("�����ڴ˱�");
                            }
                        } else {
                            UI::footer("��ʽ����");
                        }
                    } else {
                        UI::footer("��ʽ����");
                    }
                }
                    break;
                case 2: // �ڽӶ���
                    if (graph == nullptr) {
                        UI::footer("ͼΪ�գ�");
                        break;
                    }
                    if (UI_inputInt(&num, "������㣺")) {
                        UI::footer("���ڵ㣺" + join(graph->adjacent(num), ", "));
                    } else {
                        UI::footer("��ʽ����");
                    }
                    break;
                case 3: // DFN
                    if (graph == nullptr) {
                        UI::footer("ͼΪ�գ�");
                        break;
                    }
                    UI::footer("DFN��" + join(graph->dfn(), ", "));
                    break;
                case 4: // BFN
                    if (graph == nullptr) {
                        UI::footer("ͼΪ�գ�");
                        break;
                    }
                    UI::footer("BFN��" + join(graph->bfn(), ", "));
                    break;
                case 5: // Floyd
                {
                    if (graph == nullptr) {
                        UI::footer("ͼΪ�գ�");
                        break;
                    }
                    int u, v, w;
                    if (UI_inputInt(&num, "��������ʼ�㣺")) {
                        u = num;
                        if (UI_inputInt(&num, "�������յ㣺")) {
                            v = num;
                            graph->floyd();
                            w = (*graph)[u][v];
                            if (w < Graph::INF) {
                                UI::footer("���ȣ�" + toString(w) + "��·����" + join(graph->findPath(u, v), " -> "));
                            } else {
                                UI::footer("����ͨ");
                            }
                        } else {
                            UI::footer("��ʽ����");
                        }
                    } else {
                        UI::footer("��ʽ����");
                    }
                }
                    break;
                case 6: // Prim
                    if (graph == nullptr) {
                        UI::footer("ͼΪ�գ�");
                        break;
                    }
                    UI::footer("Prim��" + toString(graph->prim()));
                    break;
                case 7: // Kruskal
                    if (graph == nullptr) {
                        UI::footer("ͼΪ�գ�");
                        break;
                    }
                    UI::footer("Kruskal��" + toString(graph->kruskal()));
                    break;
                case 8: // �ͷ�ͼ
                    if (graph == nullptr) {
                        UI::footer("ͼΪ�գ�");
                        break;
                    }
                    delete graph;
                    graph = nullptr;
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
    if (graph != nullptr) {
        string content = "����������һ����񣬵��������˹�����\n";
        for (int i = 1; i <= graph->getN(); i++) {
            vector<int> line((*graph)[i] + 1, (*graph)[i] + 1 + graph->getN());
            content += join(line, ", ") + "\n";
            dataView->setContents(content);
        }
    } else
        dataView->setContents("û��ͼ");
    //UI::reRender();
}
