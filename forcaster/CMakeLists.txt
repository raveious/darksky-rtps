
cmake_minimum_required(VERSION 3.7)

project(forcaster CXX)

# Set C++11
set(CMAKE_CXX_STANDARD 11)

# Find all of the packages that need to be installed.
find_package(cpprestsdk)
find_package(fastcdr)
find_package(fastrtps)

# Add code generation functions
include(IDLGeneration)

# Find all of the source files
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)

# Generate the source from IDL files
fastrtpsgen("${IDL_SOURCE}" SOURCES)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Production forcaster executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} cpprestsdk::cpprest fastrtps boost_system ssl crypto)

