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

enum Column { // ��ʾ��ǰ�û��ڿ�����һ��
    MENU = 0, RECORD_TABLE
} curCul;

void MainScene_inLoopMenu();

void MainScene_inLoopTable();

void updateTableData();

/**
 * ��ʼ��
 */
void MainScene_init() {
    /*
     * �ұ��������
     */
    vector<string> columnName = {
            "�±�",
            "����"
    };
    int columnWidth[] = {20, 20};
    READ_SPEC = true;
    dataTable = Table_create(SIDE_WIDTH, 0, VIEW_WIDTH, 27, -1, -1);
    Table_setColumnTitle(dataTable, columnName, columnWidth, TABLE_COLUMN_NUM);
    /*
     * ɸѡ����ѡ��
     */
    vector<string> menuName = {
            "  ��������",
            "  ���",
            "  ����",
            "  ����"
    };
    dataMenu = Menu_create(4, 5, menuName, 4, 0);
    /*
     * ��ʼ������
     */
    curCul = MENU;
    //
    UI_setFooterUpdate("");
    UI_startScene(nullptr);
    updateTableData();
}

void MainScene_inLoop() {
    /*
     * �л��߼�
     */
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_TAB) {
            // �л�����
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
            // �˳�����
            UI_endScene();
        }
    }
    /*
     * ��������
     */
    if (curCul == MENU) {
        MainScene_inLoopMenu();
    } else if (curCul == RECORD_TABLE) {
        MainScene_inLoopTable();
    }
}

/**
 * ������
 */
void MainScene_inLoopTable() {
    Table_inLoop(dataTable);
    if (READ_SPEC) {
        // Nothing
    }
}

/**
 * �˵�����
 */
void MainScene_inLoopMenu() {
    int num, ind, *data;
    Menu_inLoop(dataMenu);
    if (READ_SPEC) {
        if (SPEC_KEY == KEY_ENTER) {
            switch (dataMenu->cur) {
                case 0: // ��������,
                    queue.clear();
                    UI_setFooterUpdate("�����ɹ�");
                    break;
                case 1: // ���
                    if (UI_inputInt(&num, "���������ݣ�")) {
                        queue.push_back(num);
                        UI_setFooterUpdate("����ɹ�");
                    }
                    break;
                case 2: // ����
                    queue.pop_front();
                    UI_setFooterUpdate("���ӳɹ�");
                    break;
                case 3: // ����
                    data = queue.top();
                    if (data == nullptr)
                        UI_setFooterUpdate("���п�");
                    else
                        UI_setFooterUpdate("���ף�" + toIntString(*data));
                    break;
            }
            updateTableData();
        }
    }
}

int MainScene_render(int line) {
    /*
     * �Ҳ���ͼ
     */
    Table_render(dataTable, line);
    /*
     * �����ͼ
     */
    line += 1;
    Menu_render(dataMenu, line);
    return line;
}

/*
 * ���ݸ���
 */

/**
 * ���������������ݱ�
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