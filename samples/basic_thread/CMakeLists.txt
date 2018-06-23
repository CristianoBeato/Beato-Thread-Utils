# file CMakeLists.txt
cmake_minimum_required(VERSION 2.6)

add_executable(BasicThread main.cpp)
target_link_libraries(BasicThread ${SDL2_LIBRARIES} ${LIBRARY_NAME})
add_dependencies(BasicThread ${LIBRARY_NAME})