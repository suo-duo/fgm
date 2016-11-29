cmake_minimum_required (VERSION 3.6)
project (fgm)

set (SOURCE_FILES
        src/main.cpp
        src/AnimatedSprite.cpp
        src/Animation.cpp)
add_executable (fgm ${SOURCE_FILES})
target_link_libraries (fgm sfml-system sfml-window sfml-graphics)

configure_file (player.png ${CMAKE_CURRENT_BINARY_DIR}/player.png COPYONLY)
configure_file (caravan.png ${CMAKE_CURRENT_BINARY_DIR}/caravan.png COPYONLY)