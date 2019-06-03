//
// Created by guyis on 2019/3/25.
//
#include <malloc.h>
#include <string.h>

#ifndef FRESHMAN_PROJ_C_MEMORYUTIL_H
#define FRESHMAN_PROJ_C_MEMORYUTIL_H

#define MALLOC(type) (type*)malloc(sizeof(type))
#define CLONE(type,data) (type*)memcpy(MALLOC(type),data,sizeof(type))

#endif //FRESHMAN_PROJ_C_MEMORYUTIL_H
