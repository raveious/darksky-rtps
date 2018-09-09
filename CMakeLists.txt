
cmake_minimum_required(VERSION 3.7)

set(BUILD_SAMPLES OFF CACHE BOOL "Enables sample applications from cpprest")
add_subdirectory(cpprestsdk)

project(forcaster)

set(CMAKE_CXX_STANDARD 11)

add_executable(forcaster main.cc)

add_dependencies(forcaster cpprest)
target_link_libraries(forcaster cpprest)
