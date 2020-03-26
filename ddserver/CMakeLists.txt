cmake_minimum_required(VERSION 2.8)
project(ddserver)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -g -std=c++11 -Wall -Wno-unused-function")

set(LIB_SRC
    ./Logger.cpp
    )

add_library(ddserver SHARED ${LIB_SRC})

add_executable(test tests/test.cpp)
add_dependencies(test ddserver)
target_link_libraries(test ddserver)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
