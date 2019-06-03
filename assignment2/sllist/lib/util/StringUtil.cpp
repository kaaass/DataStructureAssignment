//
// Created by guyis on 2019/3/18.
//

#include <stdio.h>
#include "StringUtil.h"
#include <string>

#ifdef _WIN32

#include <stringapiset.h>

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
