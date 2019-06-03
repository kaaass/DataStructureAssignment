add_executable(huffman ${libs} main.cpp DataType.cpp DataType.h Config.h Config.cpp FileStructure.cpp FileStructure.h HashUtil.cpp HashUtil.h)
target_link_libraries(huffman uiLib)