cmake_minimum_required (VERSION 3.0)
project (fgm)

# Export compile commands
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set target name and source files
set (TARGET_NAME ${CMAKE_PROJECT_NAME})
set (SOURCE_FILES
        src/main.cpp
        src/AnimatedSprite.cpp
        src/Animation.cpp)

# Define executable
add_executable (${TARGET_NAME} ${SOURCE_FILES})

# Link libraries
target_link_libraries (${TARGET_NAME} sfml-system sfml-window sfml-graphics)

# Copy assets directory
add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets)
