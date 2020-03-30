cmake_minimum_required(VERSION 2.8)
project(ddserver)
#include_directories(${PROJECT_SOURCE_DIR}/base)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -g -std=c++11 -D_PHTREADS -Wall -Wno-unused-function -lpthread")

set(LIB_SRC
    ./Logger.cpp
    ./util.cpp 
    ./CountDownLatch.cpp 
    ./Epoll.cpp 
    ./Event.cpp 
    ./EventLoop.cpp 
    ./EventLoopThread.cpp   
    ./EventLoopThreadPool.cpp
    ./RequestContent.cpp 
    ./TcpServer.cpp 
    ./Thread.cpp 
    ./ThreadPool.cpp 
    ./Timer.cpp 
    )
add_library(ddserver SHARED ${LIB_SRC})
target_link_libraries(ddserver pthread)
add_executable(test main.cpp)
add_dependencies(test ddserver)
target_link_libraries(test ddserver)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
