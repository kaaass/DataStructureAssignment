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
     * 右边栏：树
     */
    UI::setReadSpec(true);
    dataView = new TextView(SIDE_WIDTH, 0, VIEW_WIDTH, 27);
    /*
     * 筛选条件选单
     */
    vector<string> menuName = {
            "  创建森林       ",
            "  插入一棵树",
            "  先根遍历（递归）",
            "  中根遍历（递归）",
            "  先根遍历（迭代）",
            "  中根遍历（迭代）",
            "  层次遍历",
            "  查找结点",
            "  删除结点与子树",
            "  释放森林"
    };
    dataMenu = new Menu(4, 5, menuName, 0);
    /*
     * 初始化数据
     */
    curCul = MENU;
    pForest = nullptr;
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
         * "  创建森林       ",
            "  插入一棵树",
            "  先根遍历（递归）",
            "  中根遍历（递归）",
            "  先根遍历（迭代）",
            "  中根遍历（迭代）",
            "  层次遍历",
            "  查找结点",
            "  删除结点与子树",
            "  释放森林"
         */
        if (UI::specKey() == KEY_ENTER) {
            switch (dataMenu->getCur()) {
                case 0: // 创建森林
                    pForest = new forest<int>;
                    UI::footer("创建森林成功！");
                    break;
                case 1: // 插入一棵树
                    if (pForest == nullptr) {
                        UI::footer("森林为空！");
                        break;
                    }
                    {
                        str = UI_inputString("请输入表示多叉树的扩展先根序列（左子右兄弟）：");
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
                            UI::footer("添加失败！请检查序列");
                        } else {
                            pForest->addTrees(tree);
                            UI::footer("添加成功");
                        }
                    }
                    break;
                case 2: // 先根遍历（递归）
                    if (pForest == nullptr) {
                        UI::footer("森林为空！");
                        break;
                    }
                    UI::footer("先根遍历：" + mergeBlanks(pForest->dlr()));
                    break;
                case 3: // 后根遍历（递归）
                    if (pForest == nullptr) {
                        UI::footer("森林为空！");
                        break;
                    }
                    UI::footer("后根遍历：" + mergeBlanks(pForest->lrd()));
                    break;
                case 4: // 先根遍历（迭代）
                    if (pForest == nullptr) {
                        UI::footer("森林为空！");
                        break;
                    }
                    UI::footer("先根遍历：" + pForest->dlrNonRec());
                    break;
                case 5: // 后根遍历（迭代）
                    if (pForest == nullptr) {
                        UI::footer("森林为空！");
                        break;
                    }
                    UI::footer("后根遍历：" + pForest->lrdNonRec());
                    break;
                case 6: // 层次遍历
                    if (pForest == nullptr) {
                        UI::footer("森林为空！");
                        break;
                    }
                    UI::footer("层次遍历：" + pForest->bfs());
                    break;
                case 7: // 查找结点
                    if (pForest == nullptr) {
                        UI::footer("森林为空！");
                        break;
                    }
                    if (UI_inputInt(&num, "请输入要查找的结点：")) {
                        auto ret = pForest->find(num);
                        if (ret.size() == 0) {
                            UI::footer("未找到");
                        } else {
                            UI::footer("共找到" + toIntString(ret.size()) + "个结果。");
                        }
                        break;
                    } else {
                        UI::footer("输入格式错误！");
                    }
                    break;
                case 8: // 删除结点与子树
                    if (pForest == nullptr) {
                        UI::footer("森林为空！");
                        break;
                    }
                    {
                        if (UI_inputInt(&num, "请输入要删除的结点的内容：")) {
                            bool ret = pForest->delSub(num);
                            if (!ret) {
                                UI::footer("找不到该结点！");
                            } else {
                                UI::footer("删除成功！");
                            }
                        } else {
                            UI::footer("输入格式错误！");
                        }
                    }
                    break;
                case 9: // 释放森林
                    if (pForest == nullptr) {
                        UI::footer("森林为空！");
                        break;
                    }
                    delete pForest;
                    pForest = nullptr;
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
    // Database_destroy(purchaseRecords);
    if (pForest != nullptr) {
        auto trees = pForest->getTrees();
        string contents;
        int cnt = 1;
        for (auto tree: trees) {
            contents += "子树" + toIntString(cnt++) + "：\n" + tree->toString() + "\n";
        }
        dataView->setContents(contents);
    } else {
        dataView->setContents("森林空");
    }
    //UI::reRender();
}
