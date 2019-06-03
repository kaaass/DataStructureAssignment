#include <iostream>
#include <ui/UI.h>
#include "queue.h"

using namespace std;

int main() {
    UI_mainLoop();
    /*cout << "****创建队列****" << endl;
    Queue<int> queue;
    cout << "=>" << queue.size() << " 元素" << endl;

    cout << "****入队（以-1结束）****" << endl;
    int cur;
    while (cin >> cur, cur != -1) {
        queue.push_back(cur);
    }
    cout << "=>插入成功" << endl;

    cout << "****读取队首****" << endl;
    cout << "=>" << *queue.top() << endl;

    cout << "****出队****" << endl;
    cout << "=>";
    while (!queue.empty()) {
        cout << *queue.top() << " ";
        queue.pop_front();
    }*/
    return 0;
}