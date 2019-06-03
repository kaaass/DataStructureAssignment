//
// Created by guyis on 2019/6/1.
//

#ifndef DATA_STRCUT_ASSIGN_CONFIG_H
#define DATA_STRCUT_ASSIGN_CONFIG_H

// 默认内存小端，不过我也没测试过
#define MEM_LITLLE_ENDIAN
// #define MEM_BIG_ENDIAN

// 默认存储小端
// #define MEM_LITLLE_ENDIAN
#define FILE_BIG_ENDIAN

#define MAX_DATA_BLOCK_SIZE 255
#define MAX_TREE_SEG_SIZE 255

class Config {
public:
    static bool isMemBigEndian();

    static void checkEndianConfig();
};

#endif //DATA_STRCUT_ASSIGN_CONFIG_H
