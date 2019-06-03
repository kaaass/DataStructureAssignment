//
// Created by guyis on 2019/4/19.
//

#include "../UI.h"
#include "../Table.h"
#include "../Menu.h"
#include "../UI_Utils.h"
#include "MainScene.h"
#include "../../../queue.h"

#define SIDE_WIDTH 30
#define VIEW_WIDTH 43
#define TABLE_COLUMN_NUM 2

using namespace std;

Table *dataTable;
Menu *dataMenu;
Queue<int> queue;

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
            "  创建队列",
            "  入队",
            "  出队",
            "  队首"
    };
    dataMenu = Menu_create(4, 5, menuName, 4, 0);
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
                case 0: // 创建队列,
                    queue.clear();
                    UI_setFooterUpdate("创建成功");
                    break;
                case 1: // 入队
                    if (UI_inputInt(&num, "请输入数据：")) {
                        queue.push_back(num);
                        UI_setFooterUpdate("插入成功");
                    }
                    break;
                case 2: // 出队
                    queue.pop_front();
                    UI_setFooterUpdate("出队成功");
                    break;
                case 3: // 队首
                    data = queue.top();
                    if (data == nullptr)
                        UI_setFooterUpdate("队列空");
                    else
                        UI_setFooterUpdate("队首：" + toIntString(*data));
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