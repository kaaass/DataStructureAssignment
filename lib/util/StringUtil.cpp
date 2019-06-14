//
// Created by guyis on 2019/3/18.
//

#include <stdio.h>
#include "StringUtil.h"
#include <string>

#ifdef _WIN32

#include <stringapiset.h>
#include <sstream>

#endif // _WIN32

/**
 * 判断字符串是否为空
 * @param str
 * @return
 */
bool empty(std::string str) {
    return str.empty();
}

/**
 * 转换为整数字符串
 * @param val
 * @return
 */
std::string toIntString(int val) {
    char buf[100];
    sprintf(buf, "%d", val);
    return std::string(buf);
}

/**
 * 读入一行字符串
 * @return
 */
std::string readLine() {
    char buf[100];
    gets(buf);
    return std::string(buf);
}

std::vector<std::string> splitStrs(std::string str, char split) {
    std::vector<std::string> ret;
    auto it = str.begin(), st = str.begin();
    for (; it != str.end(); it++) {
        st = it;
        while (it != str.end() && *it != split) it++;
        ret.emplace_back(st, it);
        if (it == str.end()) break;
    }
    if (str[str.size() - 1] == split) ret.emplace_back("");
    return ret;
}

/**
 * 分割字符串为若干行
 * @return
 */
std::vector<std::string> splitLines(std::string str) {
    return splitStrs(str, '\n');
}

std::string unLines(std::vector<std::string> strs) {
    return join(std::move(strs), "\n");
}

std::string mergeBlanks(const std::string& str) {
    std::string ret;
    char lst = '\0';
    for (auto ch: str) {
        if (ch == ' ' && lst == ' ')
            continue;
        ret.push_back(ch);
        lst = ch;
    }
    return ret;
}

int stringToInt(const std::string &str) {
    char *end;
    return strtol(str.c_str(), &end, 10);
}