
cmake_minimum_required(VERSION 3.7)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/idl/cmake/modules/")
find_file(IDL_SOURCE weather.idl ${CMAKE_CURRENT_SOURCE_DIR}/idl/)

# Set C++11
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(forcaster)
add_subdirectory(whisper)
