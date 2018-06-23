# file CMakeLists.txt
cmake_minimum_required(VERSION 2.6)

add_executable(sample_EventDriven main.cpp)
target_link_libraries(sample_EventDriven ${SDL2_LIBRARIES} ${LIBRARY_NAME})
add_dependencies(sample_EventDriven ${LIBRARY_NAME})