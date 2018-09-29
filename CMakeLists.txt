
cmake_minimum_required(VERSION 3.7)

project(forcaster)

# Set C++11
set(CMAKE_CXX_STANDARD 11)

# Find all of the packages that need to be installed.
find_package(cpprestsdk)
find_package(fastcdr)
find_package(fastrtps)

# Add code generation functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/idl/cmake/modules/")
include(IDLGeneration)

# Find all of the source files
find_file(IDL_SOURCE weather.idl ${CMAKE_CURRENT_SOURCE_DIR}/idl/)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*)

# Generate the source from IDL files
fastrtpsgen("${IDL_SOURCE}" SOURCES)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(forcaster ${SOURCES})

target_link_libraries(forcaster cpprestsdk::cpprest fastrtps boost_system ssl crypto)
