# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ddqp/csapp/ddserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ddqp/csapp/ddserver/build

# Include any dependencies generated for this target.
include CMakeFiles/ddserver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ddserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ddserver.dir/flags.make

CMakeFiles/ddserver.dir/Logger.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/Logger.cpp.o: ../Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ddserver.dir/Logger.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/Logger.cpp.o -c /home/ddqp/csapp/ddserver/Logger.cpp

CMakeFiles/ddserver.dir/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/Logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/Logger.cpp > CMakeFiles/ddserver.dir/Logger.cpp.i

CMakeFiles/ddserver.dir/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/Logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/Logger.cpp -o CMakeFiles/ddserver.dir/Logger.cpp.s

CMakeFiles/ddserver.dir/Logger.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/Logger.cpp.o.requires

CMakeFiles/ddserver.dir/Logger.cpp.o.provides: CMakeFiles/ddserver.dir/Logger.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/Logger.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/Logger.cpp.o.provides

CMakeFiles/ddserver.dir/Logger.cpp.o.provides.build: CMakeFiles/ddserver.dir/Logger.cpp.o


CMakeFiles/ddserver.dir/util.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/util.cpp.o: ../util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ddserver.dir/util.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/util.cpp.o -c /home/ddqp/csapp/ddserver/util.cpp

CMakeFiles/ddserver.dir/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/util.cpp > CMakeFiles/ddserver.dir/util.cpp.i

CMakeFiles/ddserver.dir/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/util.cpp -o CMakeFiles/ddserver.dir/util.cpp.s

CMakeFiles/ddserver.dir/util.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/util.cpp.o.requires

CMakeFiles/ddserver.dir/util.cpp.o.provides: CMakeFiles/ddserver.dir/util.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/util.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/util.cpp.o.provides

CMakeFiles/ddserver.dir/util.cpp.o.provides.build: CMakeFiles/ddserver.dir/util.cpp.o


CMakeFiles/ddserver.dir/CountDownLatch.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/CountDownLatch.cpp.o: ../CountDownLatch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ddserver.dir/CountDownLatch.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/CountDownLatch.cpp.o -c /home/ddqp/csapp/ddserver/CountDownLatch.cpp

CMakeFiles/ddserver.dir/CountDownLatch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/CountDownLatch.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/CountDownLatch.cpp > CMakeFiles/ddserver.dir/CountDownLatch.cpp.i

CMakeFiles/ddserver.dir/CountDownLatch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/CountDownLatch.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/CountDownLatch.cpp -o CMakeFiles/ddserver.dir/CountDownLatch.cpp.s

CMakeFiles/ddserver.dir/CountDownLatch.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/CountDownLatch.cpp.o.requires

CMakeFiles/ddserver.dir/CountDownLatch.cpp.o.provides: CMakeFiles/ddserver.dir/CountDownLatch.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/CountDownLatch.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/CountDownLatch.cpp.o.provides

CMakeFiles/ddserver.dir/CountDownLatch.cpp.o.provides.build: CMakeFiles/ddserver.dir/CountDownLatch.cpp.o


CMakeFiles/ddserver.dir/Epoll.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/Epoll.cpp.o: ../Epoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ddserver.dir/Epoll.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/Epoll.cpp.o -c /home/ddqp/csapp/ddserver/Epoll.cpp

CMakeFiles/ddserver.dir/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/Epoll.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/Epoll.cpp > CMakeFiles/ddserver.dir/Epoll.cpp.i

CMakeFiles/ddserver.dir/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/Epoll.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/Epoll.cpp -o CMakeFiles/ddserver.dir/Epoll.cpp.s

CMakeFiles/ddserver.dir/Epoll.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/Epoll.cpp.o.requires

CMakeFiles/ddserver.dir/Epoll.cpp.o.provides: CMakeFiles/ddserver.dir/Epoll.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/Epoll.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/Epoll.cpp.o.provides

CMakeFiles/ddserver.dir/Epoll.cpp.o.provides.build: CMakeFiles/ddserver.dir/Epoll.cpp.o


CMakeFiles/ddserver.dir/Event.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/Event.cpp.o: ../Event.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ddserver.dir/Event.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/Event.cpp.o -c /home/ddqp/csapp/ddserver/Event.cpp

CMakeFiles/ddserver.dir/Event.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/Event.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/Event.cpp > CMakeFiles/ddserver.dir/Event.cpp.i

CMakeFiles/ddserver.dir/Event.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/Event.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/Event.cpp -o CMakeFiles/ddserver.dir/Event.cpp.s

CMakeFiles/ddserver.dir/Event.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/Event.cpp.o.requires

CMakeFiles/ddserver.dir/Event.cpp.o.provides: CMakeFiles/ddserver.dir/Event.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/Event.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/Event.cpp.o.provides

CMakeFiles/ddserver.dir/Event.cpp.o.provides.build: CMakeFiles/ddserver.dir/Event.cpp.o


CMakeFiles/ddserver.dir/EventLoop.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/EventLoop.cpp.o: ../EventLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ddserver.dir/EventLoop.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/EventLoop.cpp.o -c /home/ddqp/csapp/ddserver/EventLoop.cpp

CMakeFiles/ddserver.dir/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/EventLoop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/EventLoop.cpp > CMakeFiles/ddserver.dir/EventLoop.cpp.i

CMakeFiles/ddserver.dir/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/EventLoop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/EventLoop.cpp -o CMakeFiles/ddserver.dir/EventLoop.cpp.s

CMakeFiles/ddserver.dir/EventLoop.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/EventLoop.cpp.o.requires

CMakeFiles/ddserver.dir/EventLoop.cpp.o.provides: CMakeFiles/ddserver.dir/EventLoop.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/EventLoop.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/EventLoop.cpp.o.provides

CMakeFiles/ddserver.dir/EventLoop.cpp.o.provides.build: CMakeFiles/ddserver.dir/EventLoop.cpp.o


CMakeFiles/ddserver.dir/EventLoopThread.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/EventLoopThread.cpp.o: ../EventLoopThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ddserver.dir/EventLoopThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/EventLoopThread.cpp.o -c /home/ddqp/csapp/ddserver/EventLoopThread.cpp

CMakeFiles/ddserver.dir/EventLoopThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/EventLoopThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/EventLoopThread.cpp > CMakeFiles/ddserver.dir/EventLoopThread.cpp.i

CMakeFiles/ddserver.dir/EventLoopThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/EventLoopThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/EventLoopThread.cpp -o CMakeFiles/ddserver.dir/EventLoopThread.cpp.s

CMakeFiles/ddserver.dir/EventLoopThread.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/EventLoopThread.cpp.o.requires

CMakeFiles/ddserver.dir/EventLoopThread.cpp.o.provides: CMakeFiles/ddserver.dir/EventLoopThread.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/EventLoopThread.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/EventLoopThread.cpp.o.provides

CMakeFiles/ddserver.dir/EventLoopThread.cpp.o.provides.build: CMakeFiles/ddserver.dir/EventLoopThread.cpp.o


CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o: ../EventLoopThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o -c /home/ddqp/csapp/ddserver/EventLoopThreadPool.cpp

CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/EventLoopThreadPool.cpp > CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.i

CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/EventLoopThreadPool.cpp -o CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.s

CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o.requires

CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o.provides: CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o.provides

CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o.provides.build: CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o


CMakeFiles/ddserver.dir/RequestContent.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/RequestContent.cpp.o: ../RequestContent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ddserver.dir/RequestContent.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/RequestContent.cpp.o -c /home/ddqp/csapp/ddserver/RequestContent.cpp

CMakeFiles/ddserver.dir/RequestContent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/RequestContent.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/RequestContent.cpp > CMakeFiles/ddserver.dir/RequestContent.cpp.i

CMakeFiles/ddserver.dir/RequestContent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/RequestContent.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/RequestContent.cpp -o CMakeFiles/ddserver.dir/RequestContent.cpp.s

CMakeFiles/ddserver.dir/RequestContent.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/RequestContent.cpp.o.requires

CMakeFiles/ddserver.dir/RequestContent.cpp.o.provides: CMakeFiles/ddserver.dir/RequestContent.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/RequestContent.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/RequestContent.cpp.o.provides

CMakeFiles/ddserver.dir/RequestContent.cpp.o.provides.build: CMakeFiles/ddserver.dir/RequestContent.cpp.o


CMakeFiles/ddserver.dir/TcpServer.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/TcpServer.cpp.o: ../TcpServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/ddserver.dir/TcpServer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/TcpServer.cpp.o -c /home/ddqp/csapp/ddserver/TcpServer.cpp

CMakeFiles/ddserver.dir/TcpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/TcpServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/TcpServer.cpp > CMakeFiles/ddserver.dir/TcpServer.cpp.i

CMakeFiles/ddserver.dir/TcpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/TcpServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/TcpServer.cpp -o CMakeFiles/ddserver.dir/TcpServer.cpp.s

CMakeFiles/ddserver.dir/TcpServer.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/TcpServer.cpp.o.requires

CMakeFiles/ddserver.dir/TcpServer.cpp.o.provides: CMakeFiles/ddserver.dir/TcpServer.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/TcpServer.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/TcpServer.cpp.o.provides

CMakeFiles/ddserver.dir/TcpServer.cpp.o.provides.build: CMakeFiles/ddserver.dir/TcpServer.cpp.o


CMakeFiles/ddserver.dir/Thread.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/Thread.cpp.o: ../Thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/ddserver.dir/Thread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/Thread.cpp.o -c /home/ddqp/csapp/ddserver/Thread.cpp

CMakeFiles/ddserver.dir/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/Thread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/Thread.cpp > CMakeFiles/ddserver.dir/Thread.cpp.i

CMakeFiles/ddserver.dir/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/Thread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/Thread.cpp -o CMakeFiles/ddserver.dir/Thread.cpp.s

CMakeFiles/ddserver.dir/Thread.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/Thread.cpp.o.requires

CMakeFiles/ddserver.dir/Thread.cpp.o.provides: CMakeFiles/ddserver.dir/Thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/Thread.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/Thread.cpp.o.provides

CMakeFiles/ddserver.dir/Thread.cpp.o.provides.build: CMakeFiles/ddserver.dir/Thread.cpp.o


CMakeFiles/ddserver.dir/ThreadPool.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/ThreadPool.cpp.o: ../ThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/ddserver.dir/ThreadPool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/ThreadPool.cpp.o -c /home/ddqp/csapp/ddserver/ThreadPool.cpp

CMakeFiles/ddserver.dir/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/ThreadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/ThreadPool.cpp > CMakeFiles/ddserver.dir/ThreadPool.cpp.i

CMakeFiles/ddserver.dir/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/ThreadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/ThreadPool.cpp -o CMakeFiles/ddserver.dir/ThreadPool.cpp.s

CMakeFiles/ddserver.dir/ThreadPool.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/ThreadPool.cpp.o.requires

CMakeFiles/ddserver.dir/ThreadPool.cpp.o.provides: CMakeFiles/ddserver.dir/ThreadPool.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/ThreadPool.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/ThreadPool.cpp.o.provides

CMakeFiles/ddserver.dir/ThreadPool.cpp.o.provides.build: CMakeFiles/ddserver.dir/ThreadPool.cpp.o


CMakeFiles/ddserver.dir/Timer.cpp.o: CMakeFiles/ddserver.dir/flags.make
CMakeFiles/ddserver.dir/Timer.cpp.o: ../Timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/ddserver.dir/Timer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ddserver.dir/Timer.cpp.o -c /home/ddqp/csapp/ddserver/Timer.cpp

CMakeFiles/ddserver.dir/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ddserver.dir/Timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ddqp/csapp/ddserver/Timer.cpp > CMakeFiles/ddserver.dir/Timer.cpp.i

CMakeFiles/ddserver.dir/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ddserver.dir/Timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ddqp/csapp/ddserver/Timer.cpp -o CMakeFiles/ddserver.dir/Timer.cpp.s

CMakeFiles/ddserver.dir/Timer.cpp.o.requires:

.PHONY : CMakeFiles/ddserver.dir/Timer.cpp.o.requires

CMakeFiles/ddserver.dir/Timer.cpp.o.provides: CMakeFiles/ddserver.dir/Timer.cpp.o.requires
	$(MAKE) -f CMakeFiles/ddserver.dir/build.make CMakeFiles/ddserver.dir/Timer.cpp.o.provides.build
.PHONY : CMakeFiles/ddserver.dir/Timer.cpp.o.provides

CMakeFiles/ddserver.dir/Timer.cpp.o.provides.build: CMakeFiles/ddserver.dir/Timer.cpp.o


# Object files for target ddserver
ddserver_OBJECTS = \
"CMakeFiles/ddserver.dir/Logger.cpp.o" \
"CMakeFiles/ddserver.dir/util.cpp.o" \
"CMakeFiles/ddserver.dir/CountDownLatch.cpp.o" \
"CMakeFiles/ddserver.dir/Epoll.cpp.o" \
"CMakeFiles/ddserver.dir/Event.cpp.o" \
"CMakeFiles/ddserver.dir/EventLoop.cpp.o" \
"CMakeFiles/ddserver.dir/EventLoopThread.cpp.o" \
"CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o" \
"CMakeFiles/ddserver.dir/RequestContent.cpp.o" \
"CMakeFiles/ddserver.dir/TcpServer.cpp.o" \
"CMakeFiles/ddserver.dir/Thread.cpp.o" \
"CMakeFiles/ddserver.dir/ThreadPool.cpp.o" \
"CMakeFiles/ddserver.dir/Timer.cpp.o"

# External object files for target ddserver
ddserver_EXTERNAL_OBJECTS =

../lib/libddserver.so: CMakeFiles/ddserver.dir/Logger.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/util.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/CountDownLatch.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/Epoll.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/Event.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/EventLoop.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/EventLoopThread.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/RequestContent.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/TcpServer.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/Thread.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/ThreadPool.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/Timer.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/build.make
../lib/libddserver.so: CMakeFiles/ddserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX shared library ../lib/libddserver.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ddserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ddserver.dir/build: ../lib/libddserver.so

.PHONY : CMakeFiles/ddserver.dir/build

CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/Logger.cpp.o.requires
CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/util.cpp.o.requires
CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/CountDownLatch.cpp.o.requires
CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/Epoll.cpp.o.requires
CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/Event.cpp.o.requires
CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/EventLoop.cpp.o.requires
CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/EventLoopThread.cpp.o.requires
CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/EventLoopThreadPool.cpp.o.requires
CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/RequestContent.cpp.o.requires
CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/TcpServer.cpp.o.requires
CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/Thread.cpp.o.requires
CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/ThreadPool.cpp.o.requires
CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/Timer.cpp.o.requires

.PHONY : CMakeFiles/ddserver.dir/requires

CMakeFiles/ddserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ddserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ddserver.dir/clean

CMakeFiles/ddserver.dir/depend:
	cd /home/ddqp/csapp/ddserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ddqp/csapp/ddserver /home/ddqp/csapp/ddserver /home/ddqp/csapp/ddserver/build /home/ddqp/csapp/ddserver/build /home/ddqp/csapp/ddserver/build/CMakeFiles/ddserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ddserver.dir/depend

