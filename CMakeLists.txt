cmake_minimum_required(VERSION 3.0.0)
project(yae VERSION 0.0.1)

include(CTest)
enable_testing()

# Set compile flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Set output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Set definitions
add_compile_definitions("DEBUG")
if (APPLE)
    add_compile_definitions("OS_MAC")
elseif(UNIX)
    add_compile_definitions("OS_LINUX")
elseif(MSVC)
    add_compile_definitions("OS_WIN")
else()
    add_compile_definitions("OS_UNKNOWN")
endif()

# Set include & src paths
set(INCLUDE_PATH ${CMAKE_BINARY_DIR}/../include)
set(SRC_PATH ${CMAKE_BINARY_DIR}/../src)

# Add subprojects
add_subdirectory(${SRC_PATH}/core core)

# Include directories
include_directories(${INCLUDE_PATH} ${INCLUDE_PATH}/core)

# Locate all source files
file(
    GLOB_RECURSE  
    SRC_FILES
    
    "${SRC_PATH}/*.cpp"
)

# Add executable
add_executable(
    yae

    ${SRC_FILES}
)

target_link_libraries(yae core)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)