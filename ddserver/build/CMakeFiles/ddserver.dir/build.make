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


# Produce verbose output by default.
VERBOSE = 1

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


# Object files for target ddserver
ddserver_OBJECTS = \
"CMakeFiles/ddserver.dir/Logger.cpp.o"

# External object files for target ddserver
ddserver_EXTERNAL_OBJECTS =

../lib/libddserver.so: CMakeFiles/ddserver.dir/Logger.cpp.o
../lib/libddserver.so: CMakeFiles/ddserver.dir/build.make
../lib/libddserver.so: CMakeFiles/ddserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ddqp/csapp/ddserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../lib/libddserver.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ddserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ddserver.dir/build: ../lib/libddserver.so

.PHONY : CMakeFiles/ddserver.dir/build

CMakeFiles/ddserver.dir/requires: CMakeFiles/ddserver.dir/Logger.cpp.o.requires

.PHONY : CMakeFiles/ddserver.dir/requires

CMakeFiles/ddserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ddserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ddserver.dir/clean

CMakeFiles/ddserver.dir/depend:
	cd /home/ddqp/csapp/ddserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ddqp/csapp/ddserver /home/ddqp/csapp/ddserver /home/ddqp/csapp/ddserver/build /home/ddqp/csapp/ddserver/build /home/ddqp/csapp/ddserver/build/CMakeFiles/ddserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ddserver.dir/depend
