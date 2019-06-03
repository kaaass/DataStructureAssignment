add_subdirectory(lib)

add_executable(assignment2-queue ${libs} main.cpp queue.hpp queue.h)
target_link_libraries(assignment2-queue library-queue)
