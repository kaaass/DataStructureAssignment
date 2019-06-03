#include <iostream>
#include "List.h"

#include "lib/ui/UI.h"

using namespace std;

int main() {
    UI_mainLoop();
    /*int cur;

    cout << "****创建单链表****" << endl;
    List<int> list;
    cout << "=>" << list.size() << " 元素" << endl;

    cout << "****在表头插入（以-1结束）****" << endl;
    while (cin >> cur, cur != -1) {
        list.insert_front(cur);
    }
    cout << "=>插入成功" << endl;

    cout << "****在当前节点后插入（以-1结束）****" << endl;
    while (cin >> cur, cur != -1) {
        list.insert(cur);
    }
    cout << "=>插入成功" << endl;

    cout << "****在表尾插入（以-1结束）****" << endl;
    while (cin >> cur, cur != -1) {
        list.insert_back(cur);
    }
    cout << "=>插入成功" << endl;

    cout << "****输出顺序表****" << endl;
    cout << "=>" << list << endl;*/
    return 0;
}