#include <iostream>
#include <ui/UI.h>
#include "queue.h"

using namespace std;

int main() {
    UI_mainLoop();
    /*cout << "****��������****" << endl;
    Queue<int> queue;
    cout << "=>" << queue.size() << " Ԫ��" << endl;

    cout << "****��ӣ���-1������****" << endl;
    int cur;
    while (cin >> cur, cur != -1) {
        queue.push_back(cur);
    }
    cout << "=>����ɹ�" << endl;

    cout << "****��ȡ����****" << endl;
    cout << "=>" << *queue.top() << endl;

    cout << "****����****" << endl;
    cout << "=>";
    while (!queue.empty()) {
        cout << *queue.top() << " ";
        queue.pop_front();
    }*/
    return 0;
}