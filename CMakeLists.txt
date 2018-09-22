
cmake_minimum_required(VERSION 3.7)

project(forcaster)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(forcaster ${SOURCES})

target_link_libraries(forcaster cpprest fastrtps boost_system ssl crypto)
