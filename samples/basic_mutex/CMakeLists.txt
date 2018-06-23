# file CMakeLists.txt
cmake_minimum_required(VERSION 2.6)

add_executable(sample_BasicMutex main.cpp)
target_link_libraries(sample_BasicMutex ${SDL2_LIBRARIES} ${LIBRARY_NAME})
add_dependencies(sample_BasicMutex ${LIBRARY_NAME})