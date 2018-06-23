# file CMakeLists.txt
cmake_minimum_required(VERSION 2.6)

add_executable(BasicMutex main.cpp)
target_link_libraries(BasicMutex ${SDL2_LIBRARIES} ${LIBRARY_NAME})
add_dependencies(BasicMutex ${LIBRARY_NAME})