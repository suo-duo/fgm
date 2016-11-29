cmake_minimum_required(VERSION 3.6)
project(fgm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp AnimatedSprite.cpp Animation.cpp)
add_executable(fgm ${SOURCE_FILES})
target_link_libraries(fgm sfml-system sfml-window sfml-graphics)

configure_file(player.png ${CMAKE_CURRENT_BINARY_DIR}/player.png COPYONLY)