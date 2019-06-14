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
     * 右边栏：邻接矩阵
     */
    UI::setReadSpec(true);
    dataView = new TextView(SIDE_WIDTH, 0, VIEW_WIDTH, 27);
    /*
     * 筛选条件选单
     */
    vector<string> menuName = {
            "  从文件创建图",
            "  边权值",
            "  邻接顶点",
            "  DFN",
            "  BFN",
            "  Floyd",
            "  Prim",
            "  Kruskal",
            "  释放图"
    };
    dataMenu = new Menu(4, 5, menuName, 0);
    /*
     * 初始化数据
     */
    curCul = MENU;
    graph = nullptr;
    registerSubWidget(dataMenu);
    registerSubWidget(dataView);
}

/**
 * 初始化
 */
void MainScene::onInit() {
    UI::footer("");
    updateTableData();
}

std::string MainScene::getTitle() {
    return "主页面";
}

void MainScene::onLoop() {
    /*
     * 切换逻辑
     */
    if (UI::readSpec()) {
        if (UI::specKey() == KEY_TAB) {
            // 切换左右
            if (curCul == MENU) {
                curCul = RECORD_TABLE;
            } else if (curCul == RECORD_TABLE) {
                curCul = MENU;
            }
            UI::reRender();
            return;
        } else if (UI::specKey() == KEY_ESC) {
            // 退出场景
            UI::getInstance().endScene();
        }
    }
    /*
     * 分栏操作
     */
    if (curCul == MENU) {
        inLoopMenu();
    } else if (curCul == RECORD_TABLE) {
        inLoopTable();
    }
}

/**
 * 表格操作
 */
void MainScene::inLoopTable() {
    dataView->inLoop();
    if (UI::readSpec()) {
        // Nothing
    }
}

/**
 * 菜单操作
 */
void MainScene::inLoopMenu() {
    int num, ind, *data;
    string str;
    dataMenu->inLoop();
    if (UI::readSpec()) {
        /*
         * "  从文件创建图",
            "  边权值",
            "  邻接顶点",
            "  DFN",
            "  BFN",
            "  Floyd",
            "  Prim",
            "  Kruskal",
            "  释放图"
         */
        if (UI::specKey() == KEY_ENTER) {
            switch (dataMenu->getCur()) {
                case 0: // 从文件创建图
                    {
                        str = UI_inputString("请输入文件名：");
                        FILE *file = fopen(str.c_str(), "r");
                        if (file == nullptr) {
                            UI::footer("文件打开失败！");
                            break;
                        }
                        int n, m, u, v, w;
                        fscanf(file, "%d%d", &n, &m);
                        graph = new Graph(n);
                        while (m--) {
                            fscanf(file, "%d%d%d", &u, &v, &w);
                            graph->add(u, v, w);
                        }
                        UI::footer("创建成功");
                    }
                    break;
                case 1: // 边权值
                {
                    if (graph == nullptr) {
                        UI::footer("图为空！");
                        break;
                    }
                    int u, v, w;
                    if (UI_inputInt(&num, "请输入起始点：")) {
                        u = num;
                        if (UI_inputInt(&num, "请输入终点：")) {
                            v = num;
                            w = graph->node(u, v);
                            if (w < Graph::INF) {
                                UI::footer("边权值：" + toString(w));
                            } else {
                                UI::footer("不存在此边");
                            }
                        } else {
                            UI::footer("格式错误！");
                        }
                    } else {
                        UI::footer("格式错误！");
                    }
                }
                    break;
                case 2: // 邻接顶点
                    if (graph == nullptr) {
                        UI::footer("图为空！");
                        break;
                    }
                    if (UI_inputInt(&num, "请输入点：")) {
                        UI::footer("相邻点：" + join(graph->adjacent(num), ", "));
                    } else {
                        UI::footer("格式错误！");
                    }
                    break;
                case 3: // DFN
                    if (graph == nullptr) {
                        UI::footer("图为空！");
                        break;
                    }
                    UI::footer("DFN：" + join(graph->dfn(), ", "));
                    break;
                case 4: // BFN
                    if (graph == nullptr) {
                        UI::footer("图为空！");
                        break;
                    }
                    UI::footer("BFN：" + join(graph->bfn(), ", "));
                    break;
                case 5: // Floyd
                {
                    if (graph == nullptr) {
                        UI::footer("图为空！");
                        break;
                    }
                    int u, v, w;
                    if (UI_inputInt(&num, "请输入起始点：")) {
                        u = num;
                        if (UI_inputInt(&num, "请输入终点：")) {
                            v = num;
                            graph->floyd();
                            w = (*graph)[u][v];
                            if (w < Graph::INF) {
                                UI::footer("长度：" + toString(w) + "，路径：" + join(graph->findPath(u, v), " -> "));
                            } else {
                                UI::footer("不连通");
                            }
                        } else {
                            UI::footer("格式错误！");
                        }
                    } else {
                        UI::footer("格式错误！");
                    }
                }
                    break;
                case 6: // Prim
                    if (graph == nullptr) {
                        UI::footer("图为空！");
                        break;
                    }
                    UI::footer("Prim：" + toString(graph->prim()));
                    break;
                case 7: // Kruskal
                    if (graph == nullptr) {
                        UI::footer("图为空！");
                        break;
                    }
                    UI::footer("Kruskal：" + toString(graph->kruskal()));
                    break;
                case 8: // 释放图
                    if (graph == nullptr) {
                        UI::footer("图为空！");
                        break;
                    }
                    delete graph;
                    graph = nullptr;
                    UI::footer("释放成功！");
                    break;
            }
            updateTableData();
        }
    }
}

/*
 * 数据更新
 */

/**
 * 根据条件更新数据表
 */
void MainScene::updateTableData() {
    if (graph != nullptr) {
        string content = "本来这里是一个表格，但是我懒了哈哈哈\n";
        for (int i = 1; i <= graph->getN(); i++) {
            vector<int> line((*graph)[i] + 1, (*graph)[i] + 1 + graph->getN());
            content += join(line, ", ") + "\n";
            dataView->setContents(content);
        }
    } else
        dataView->setContents("没有图");
    //UI::reRender();
}
