cmake_minimum_required(VERSION 3.0.0)
project(core VERSION 0.0.1)

# Set include & src paths
set(INCLUDE_PATH ${CMAKE_BINARY_DIR}/../include)
set(SRC_PATH ${CMAKE_BINARY_DIR}/../src)

# Include directories
include_directories(${INCLUDE_PATH}/core)

# Locate all source files
file(
    GLOB_RECURSE  
    SRC_FILES
    
    "${SRC_PATH}/core/*.cpp"
)

# Add library
add_library(
    core

    ${SRC_FILES}
)

# Set prefix
set_target_properties(core PROPERTIES PREFIX "lib")