
cmake_minimum_required(VERSION 3.7)

set(BUILD_SAMPLES OFF CACHE BOOL "Enables sample applications from cpprest")
set(BUILD_TESTS OFF CACHE BOOL "Enables tests from cpprest")
add_subdirectory(cpprestsdk)

set(BUILD_JAVA ON CACHE BOOL "Enables fastrtpsgen tool support")
set(THIRDPARTY ON CACHE BOOL "")
add_subdirectory(Fast-RTPS)

project(forcaster)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(forcaster ${SOURCES})

add_dependencies(forcaster cpprest fastrtps)
target_link_libraries(forcaster cpprest fastrtps)
