# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /opt/CLion-2020.2.4/clion-2020.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/CLion-2020.2.4/clion-2020.2.4/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/IndexDBv1_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IndexDBv1_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IndexDBv1_1.dir/flags.make

CMakeFiles/IndexDBv1_1.dir/main.cpp.o: CMakeFiles/IndexDBv1_1.dir/flags.make
CMakeFiles/IndexDBv1_1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/IndexDBv1_1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IndexDBv1_1.dir/main.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/main.cpp

CMakeFiles/IndexDBv1_1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IndexDBv1_1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/main.cpp > CMakeFiles/IndexDBv1_1.dir/main.cpp.i

CMakeFiles/IndexDBv1_1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IndexDBv1_1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/main.cpp -o CMakeFiles/IndexDBv1_1.dir/main.cpp.s

# Object files for target IndexDBv1_1
IndexDBv1_1_OBJECTS = \
"CMakeFiles/IndexDBv1_1.dir/main.cpp.o"

# External object files for target IndexDBv1_1
IndexDBv1_1_EXTERNAL_OBJECTS =

IndexDBv1_1: CMakeFiles/IndexDBv1_1.dir/main.cpp.o
IndexDBv1_1: CMakeFiles/IndexDBv1_1.dir/build.make
IndexDBv1_1: index/Engine/libEngine.a
IndexDBv1_1: index/libindex.a
IndexDBv1_1: Server/libServer.a
IndexDBv1_1: grammar/libgrammar.a
IndexDBv1_1: index/Engine/libEngine.a
IndexDBv1_1: index/Engine/snappy/libsnappy.a
IndexDBv1_1: index/primitive/libprimitive.a
IndexDBv1_1: CMakeFiles/IndexDBv1_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable IndexDBv1_1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IndexDBv1_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IndexDBv1_1.dir/build: IndexDBv1_1

.PHONY : CMakeFiles/IndexDBv1_1.dir/build

CMakeFiles/IndexDBv1_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IndexDBv1_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IndexDBv1_1.dir/clean

CMakeFiles/IndexDBv1_1.dir/depend:
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1 /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1 /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles/IndexDBv1_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IndexDBv1_1.dir/depend

