//
// Created by guyis on 2019/6/12.
//

#include <ui/UI.h>
#include "StatScene.h"
#include "DataType.h"
#include "Compress.h"

using namespace std;

std::string StatScene::getTitle() {
    return "Ƶ��ͳ��";
}

void StatScene::onCreate() {
    title = new Label(-1, 1, 50, true);
    title->setText("Ƶ��ͳ�Ʊ�");

    vector<string> colName = {
            "�ַ�",
            "���ִ���"
    };
    int colWidth[] = {20, 20};
    statTable = new Table(-1, 3, 43, 20, 1, 1);
    statTable->setColumnTitle(colName, colWidth);

    /*
     * ��ʼ������
     */
    registerSubWidget(statTable);
    registerSubWidget(title);
}

string showChar(char ch) {
    if (ch == '\n') {
        return "\\n";
    } else if (ch == '\r') {
        return "\\r";
    } else if (ch == '\t') {
        return "\\t";
    } else {
        string str;
        str.push_back(ch);
        return str;
    }
}

void StatScene::onInit() {
    BIndex fileSize;
    std::unordered_map<UChar, int> counts = countCharBuf(file, fileSize);
    for (auto item: counts) {
        vector<string> line;
        line.push_back(showChar((char) item.first));
        line.push_back(toIntString(item.second));
        statTable->pushLine(line);
    }
    UI::footer("");
}

void StatScene::onLoop() {
    statTable->inLoop();
    if (UI::readSpec()) {
        if (UI::specKey() == KEY_ESC) {
            // �˳�����
            UI::getInstance().endScene();
        }
    }
}
