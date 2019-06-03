//
// Created by guyis on 2019/6/1.
//
#include <iostream>
#include "DataType.h"
#include "FileStructure.h"
#include "HashUtil.h"
#include "Huffman.h"
#include "Compress.h"

using namespace std;

int main() {
    Config::checkEndianConfig();
    FILE *source = fopen("comp.txt", "rb");
    FILE *dest = fopen("comp.huf", "wb");

    compressAndSave(source, dest);
    fflush(dest);

    FILE *decompSource = fopen("comp.huf", "rb");
    FILE *decomp = fopen("decomp.txt", "wb");

    decompressAndSave(decompSource, decomp);
    return 0;
}