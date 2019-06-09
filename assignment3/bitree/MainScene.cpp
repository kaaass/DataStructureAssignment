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
            "  创建二叉树     ",
            "  先根遍历（递归）",
            "  中根遍历（递归）",
            "  后根遍历（递归）",
            "  先根遍历（迭代）",
            "  中根遍历（迭代）",
            "  后根遍历（迭代）",
            "  层次遍历",
            "  查找结点及其父亲",
            "  删除子树",
            "  释放树"
    };
    dataMenu = new Menu(4, 5, menuName, 0);
    /*
     * 初始化数据
     */
    curCul = MENU;
    tree = nullptr;
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
         * 创建二叉树
            先根遍历（递归）
            中根遍历（递归）
            后根遍历（递归）
            先根遍历（迭代）
            中根遍历（迭代）
            后根遍历（迭代）
            层次遍历",
            查找结点及其父亲
            删除子树"
         */
        if (UI::specKey() == KEY_ENTER) {
            switch (dataMenu->getCur()) {
                case 0: // 创建二叉树
                    {
                        str = UI_inputString("请输入扩展先根序列：");
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
                            UI::footer("创建失败！请检查序列");
                        } else {
                            UI::footer("创建成功");
                        }
                    }
                    break;
                case 1: // 先根遍历（递归）
                    if (tree == nullptr) {
                        UI::footer("树为空！");
                        break;
                    }
                    UI::footer("先根遍历：" + mergeBlanks(bitree<int>::dlr(tree)));
                    break;
                case 2: // 中根遍历（递归）
                    if (tree == nullptr) {
                        UI::footer("树为空！");
                        break;
                    }
                    UI::footer("中根遍历：" + mergeBlanks(bitree<int>::ldr(tree)));
                    break;
                case 3: // 后根遍历（递归）
                    if (tree == nullptr) {
                        UI::footer("树为空！");
                        break;
                    }
                    UI::footer("后根遍历：" + mergeBlanks(bitree<int>::lrd(tree)));
                    break;
                case 4: // 先根遍历（迭代）
                    if (tree == nullptr) {
                        UI::footer("树为空！");
                        break;
                    }
                    UI::footer("先根遍历：" + bitree<int>::dlrNonRec(tree));
                    break;
                case 5: // 中根遍历（迭代）
                    if (tree == nullptr) {
                        UI::footer("树为空！");
                        break;
                    }
                    UI::footer("中根遍历：" + bitree<int>::ldrNonRec(tree));
                    break;
                case 6: // 后根遍历（迭代）
                    if (tree == nullptr) {
                        UI::footer("树为空！");
                        break;
                    }
                    UI::footer("后根遍历：" + bitree<int>::lrdNonRec(tree));
                    break;
                case 7: // 层次遍历
                    if (tree == nullptr) {
                        UI::footer("树为空！");
                        break;
                    }
                    UI::footer("层次遍历：" + bitree<int>::bfs(tree));
                    break;
                case 8: // 查找结点及其父亲
                    if (tree == nullptr) {
                        UI::footer("树为空！");
                        break;
                    }
                    if (UI_inputInt(&num, "请输入要查找的结点：")) {
                        string msg;
                        auto ret = tree->find(num);
                        for (auto subTree: ret) {
                            msg += "{ 结点内容 = " + toIntString(*subTree->getData()) + ", 结点父 = ";
                            if (subTree->getFather() == nullptr) {
                                msg += "无";
                            } else {
                                msg += toIntString(*subTree->getFather()->getData());
                            }
                            msg += " }, ";
                        }
                        if (ret.size() == 0) {
                            UI::footer("未找到");
                        } else {
                            UI::footer("共找到" + toIntString(ret.size()) + "个结果：" + msg);
                        }
                        break;
                    }
                    UI::footer("输入格式错误！");
                    break;
                case 9: // 删除子树
                    if (tree == nullptr) {
                        UI::footer("树为空！");
                        break;
                    }
                    {
                        str = UI_inputString("请输入确定结点的标志序列：");
                        auto sub = bitree<int>::resolveSub(tree, str);
                        if (sub == nullptr) {
                            UI::footer("找不到该结点！");
                        } else {
                            tree = bitree<int>::delFromNode(tree, sub);
                            UI::footer("删除成功！");
                        }
                    }
                    break;
                case 10: // 释放树
                    if (tree == nullptr) {
                        UI::footer("树为空！");
                        break;
                    }
                    delete tree;
                    tree = nullptr;
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
    if (tree != nullptr)
        dataView->setContents(tree->toString());
    else
        dataView->setContents("树空");
    //UI::reRender();
}
