//
// Created by guyis on 2019/6/14.
//

#ifndef DATA_STRCUT_ASSIGN_STRINGUTIL_HPP
#define DATA_STRCUT_ASSIGN_STRINGUTIL_HPP

#include <sstream>
#include "StringUtil.h"

template<typename T>
std::string join(std::vector<T> strs, std::string spl) {
    std::string ret;
    for (const auto& line: strs) {
        ret += toString(line) + spl;
    }
    return ret.substr(0, ret.size() - spl.size());
}

template<typename T>
std::string toString(T data) {
    std::ostringstream ss;
    ss << data;
    return ss.str();
}

#endif //DATA_STRCUT_ASSIGN_STRINGUTIL_HPP
