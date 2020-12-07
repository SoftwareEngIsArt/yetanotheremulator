cmake_minimum_required(VERSION 3.0.0)
project(yae VERSION 0.0.1)

include(CTest)
enable_testing()

# Configure compiler
set(CMAKE_CXX_STANDARD 14)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

# Set build enviroment definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_compile_definitions("DEBUG")
endif()
if (APPLE)
    add_compile_definitions("OS_MAC")
    set(OS_FOLDER mac)
elseif(UNIX)
    add_compile_definitions("OS_LINUX")
    set(OS_FOLDER linux)
elseif(MSVC)
    add_compile_definitions("OS_WIN")
    set(OS_FOLDER win)
else()
    add_compile_definitions("OS_UNKNOWN")
    set(OS_FOLDER unknown)
endif()

# Set output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib/${OS_FOLDER})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib/${OS_FOLDER})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/${OS_FOLDER})

# Set include & src paths
set(INCLUDE_PATH ${CMAKE_BINARY_DIR}/../include)
set(SRC_PATH ${CMAKE_BINARY_DIR}/../src)

# Include directories
include_directories(${INCLUDE_PATH})
include_directories(${INCLUDE_PATH}/core)
include_directories(${INCLUDE_PATH}/utils)

# Locate all source files
file(
    GLOB_RECURSE  
    SRC_FILES
    
    ${SRC_PATH}/*.cpp
)

# Add executable
add_executable(yae ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)