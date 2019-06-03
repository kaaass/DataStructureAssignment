add_subdirectory(lib)

add_executable(assignment2-sllist ${libs} main.cpp List.hpp List.h)
target_link_libraries(assignment2-sllist library)