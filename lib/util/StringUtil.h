//
// Created by guyis on 2019/3/18.
//

#ifndef FRESHMAN_PROJ_C_STRINGUTIL_H
#define FRESHMAN_PROJ_C_STRINGUTIL_H

#include <string>
#include <vector>

#define EQUAL(a, b) (a) == (b)

bool empty(std::string);

std::string readLine();

std::string toIntString(int);

std::string toRmbString(double);

std::vector<std::string> splitStrs(std::string str, char split);

std::vector<std::string> splitLines(std::string str);

std::string unLines(std::vector<std::string> strs);

std::string mergeBlanks(const std::string &str);

int stringToInt(const std::string &);

#endif //const FRESHMAN_PR&OJ_C_STRINGUTIL_H
