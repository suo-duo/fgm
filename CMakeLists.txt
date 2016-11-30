cmake_minimum_required (VERSION 3.2)
project (fgm)

# Export compile commands
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++14
set (CMAKE_CXX_STANDARD 14)

# Set compiler flags
# SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} " )


# Set target name and source files
set (TARGET_NAME ${CMAKE_PROJECT_NAME})
file (GLOB SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/**)

# Define executable
add_executable (${TARGET_NAME} ${SOURCE_FILES})

# Link libraries
target_link_libraries (
  ${TARGET_NAME}
  sfml-system
  sfml-window
  sfml-graphics
  folly
  boost_filesystem
  boost_system
)

# Copy assets directory
add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets)
