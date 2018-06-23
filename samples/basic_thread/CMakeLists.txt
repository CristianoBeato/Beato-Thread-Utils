# file CMakeLists.txt
cmake_minimum_required(VERSION 2.6)

add_executable(sample_BasicThread main.cpp)
target_link_libraries(sample_BasicThread ${SDL2_LIBRARIES} ${LIBRARY_NAME})
add_dependencies(sample_BasicThread ${LIBRARY_NAME})