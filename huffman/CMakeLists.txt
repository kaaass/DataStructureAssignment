set(libs
        ../assignment3/bitree.h
        ../assignment3/bitree.hpp)

add_executable(huffman ${libs} main.cpp DataType.cpp DataType.h Config.h Config.cpp FileStructure.cpp FileStructure.h HashUtil.cpp HashUtil.h Huffman.cpp Huffman.h Compress.cpp Compress.h MainScene.h MainScene.cpp InputScene.cpp InputScene.h)
target_link_libraries(huffman uiLib)