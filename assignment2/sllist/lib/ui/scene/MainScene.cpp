//
// Created by guyis on 2019/4/19.
//

#include "../UI.h"
#include "../Table.h"
#include "../Menu.h"
#include "../UI_Utils.h"
#include "MainScene.h"
#include "../../../List.h"

#define SIDE_WIDTH 30
#define VIEW_WIDTH 43
#define TABLE_COLUMN_NUM 2

using namespace std;

Table *dataTable;
Menu *dataMenu;
List<int> queue;

enum Column { // 表示当前用户在控制哪一栏
    MENU = 0, RECORD_TABLE
} curCul;

void MainScene_inLoopMenu();

void MainScene_inLoopTable();

void updateTableData();

/**
 * 初始化
 */
void MainScene_init() {
    /*
     * 右边栏：表格
     */
    vector<string> columnName = {
            "下标",
            "内容"
    };
    int columnWidth[] = {20, 20};
    READ_SPEC = true;
    dataTable = Table_create(SIDE_WIDTH, 0, VIEW_WIDTH, 27, -1, -1);
    Table_setColumnTitle(dataTable, columnName, columnWidth, TABLE_COLUMN_NUM);
    /*
     * 筛选条件选单
     */
    vector<string> menuName = {
            "  创建链表",
            "  插入：表头",
            "  插入：表尾",
            "  插入：当前结点",
            "  删除：表头",
            "  删除：表尾",
            "  删除：当前结点",
            "  存储：第k个",
            "  存储：当前结点",
            "  读取：第k个",
            "  读取：当前结点",
            "  查找"
    };
    dataMenu = Menu_create(4, 5, menuName, 12, 0);
    /*
     * 初始化数据
     */
    curCul = MENU;
    //
    UI_setFooterUpdate("");
    UI_startScene(nullptr);
    updateTableData();
}

void MainScene_inLoop() {
    /*
     * 切换逻辑
     */
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_TAB) {
            // 切换左右
            if (curCul == MENU) {
                curCul = RECORD_TABLE;
                if (dataTable->cur == -1 && !queue.empty())
                    Table_setCurAndUpdate(dataTable, 1);
            } else if (curCul == RECORD_TABLE) {
                curCul = MENU;
            }
            UI_render();
            return;
        } else if (SPEC_KEY == KEY_ESC) {
            // 退出场景
            UI_endScene();
        }
    }
    /*
     * 分栏操作
     */
    if (curCul == MENU) {
        MainScene_inLoopMenu();
    } else if (curCul == RECORD_TABLE) {
        MainScene_inLoopTable();
    }
}

/**
 * 表格操作
 */
void MainScene_inLoopTable() {
    Table_inLoop(dataTable);
    if (READ_SPEC) {
        // Nothing
    }
}

/**
 * 菜单操作
 */
void MainScene_inLoopMenu() {
    int num, ind, *data;
    Menu_inLoop(dataMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            switch (dataMenu->cur) {
                case 0: // 创建链表
                    queue.clear();
                    UI_setFooterUpdate("创建成功");
                    break;
                case 1: // 插入：表头
                    if (UI_inputInt(&num, "请输入数据：")) {
                        queue.insert_front(num);
                        UI_setFooterUpdate("插入成功");
                    }
                    break;
                case 2: // 插入：表尾
                    if (UI_inputInt(&num, "请输入数据：")) {
                        queue.insert_back(num);
                        UI_setFooterUpdate("插入成功");
                    }
                    break;
                case 3: // 插入：当前结点
                    if (UI_inputInt(&num, "请输入数据：")) {
                        queue.insert(num);
                        UI_setFooterUpdate("插入成功");
                    }
                    break;
                case 4: // 删除：表头
                    queue.remove_front();
                    UI_setFooterUpdate("删除成功");
                    break;
                case 5: // 删除：表尾
                    queue.remove_back();
                    UI_setFooterUpdate("删除成功");
                    break;
                case 6: // 删除：当前结点
                    queue.remove();
                    UI_setFooterUpdate("删除成功");
                    break;
                case 7: // 存储：第k个
                    if (UI_inputInt(&ind, "请输入第k个：")) {
                        if (UI_inputInt(&num, "请输入数据：")) {
                            queue.set(num, ind);
                            UI_setFooterUpdate("存储成功");
                        }
                    }
                    break;
                case 8: // 存储：当前结点
                    if (UI_inputInt(&num, "请输入数据：")) {
                        queue.set(num);
                        UI_setFooterUpdate("存储成功");
                    }
                    break;
                case 9: // 读取：第k个
                    if (UI_inputInt(&ind, "请输入第k个：")) {
                        data = queue.get(ind);
                        if (data != nullptr)
                            UI_setFooterUpdate(toIntString(*data));
                    }
                    break;
                case 10: // 读取：当前结点
                    data = queue.get();
                    if (data != nullptr)
                        UI_setFooterUpdate(toIntString(*data));
                    break;
                case 11: // 查找
                    if (UI_inputInt(&num, "请输入数据：")) {
                        UI_setFooterUpdate("查找成功，于：" + toIntString(queue.search(num)));
                    }
                    break;
            }
            updateTableData();
        }
    }
}

int MainScene_render(int line) {
    /*
     * 右侧试图
     */
    Table_render(dataTable, line);
    /*
     * 左侧视图
     */
    line += 1;
    Menu_render(dataMenu, line);
    return line;
}

/*
 * 数据更新
 */

/**
 * 根据条件更新数据表
 */
void updateTableData() {
    Table_clear(dataTable);
    // Database_destroy(purchaseRecords);
    for (int i = 0; i < queue.size(); i++) {
        vector<string> tmp;
        tmp.push_back(toIntString(i));
        tmp.push_back(toIntString(*queue.get(i)));
        Table_pushLine(dataTable, tmp);
    }
    if (!queue.empty())
        Table_setCur(dataTable, 1);
    UI_render();
}