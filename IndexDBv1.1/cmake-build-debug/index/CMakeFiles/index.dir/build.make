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
include index/CMakeFiles/index.dir/depend.make

# Include the progress variables for this target.
include index/CMakeFiles/index.dir/progress.make

# Include the compile flags for this target's objects.
include index/CMakeFiles/index.dir/flags.make

index/CMakeFiles/index.dir/cprocess.cpp.o: index/CMakeFiles/index.dir/flags.make
index/CMakeFiles/index.dir/cprocess.cpp.o: ../index/cprocess.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object index/CMakeFiles/index.dir/cprocess.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/index.dir/cprocess.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/cprocess.cpp

index/CMakeFiles/index.dir/cprocess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index.dir/cprocess.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/cprocess.cpp > CMakeFiles/index.dir/cprocess.cpp.i

index/CMakeFiles/index.dir/cprocess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index.dir/cprocess.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/cprocess.cpp -o CMakeFiles/index.dir/cprocess.cpp.s

index/CMakeFiles/index.dir/index_operation.cpp.o: index/CMakeFiles/index.dir/flags.make
index/CMakeFiles/index.dir/index_operation.cpp.o: ../index/index_operation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object index/CMakeFiles/index.dir/index_operation.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/index.dir/index_operation.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/index_operation.cpp

index/CMakeFiles/index.dir/index_operation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index.dir/index_operation.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/index_operation.cpp > CMakeFiles/index.dir/index_operation.cpp.i

index/CMakeFiles/index.dir/index_operation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index.dir/index_operation.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/index_operation.cpp -o CMakeFiles/index.dir/index_operation.cpp.s

index/CMakeFiles/index.dir/rb_tree.cpp.o: index/CMakeFiles/index.dir/flags.make
index/CMakeFiles/index.dir/rb_tree.cpp.o: ../index/rb_tree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object index/CMakeFiles/index.dir/rb_tree.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/index.dir/rb_tree.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/rb_tree.cpp

index/CMakeFiles/index.dir/rb_tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index.dir/rb_tree.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/rb_tree.cpp > CMakeFiles/index.dir/rb_tree.cpp.i

index/CMakeFiles/index.dir/rb_tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index.dir/rb_tree.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/rb_tree.cpp -o CMakeFiles/index.dir/rb_tree.cpp.s

index/CMakeFiles/index.dir/skip_list.cpp.o: index/CMakeFiles/index.dir/flags.make
index/CMakeFiles/index.dir/skip_list.cpp.o: ../index/skip_list.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object index/CMakeFiles/index.dir/skip_list.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/index.dir/skip_list.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/skip_list.cpp

index/CMakeFiles/index.dir/skip_list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index.dir/skip_list.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/skip_list.cpp > CMakeFiles/index.dir/skip_list.cpp.i

index/CMakeFiles/index.dir/skip_list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index.dir/skip_list.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/skip_list.cpp -o CMakeFiles/index.dir/skip_list.cpp.s

index/CMakeFiles/index.dir/sql.cpp.o: index/CMakeFiles/index.dir/flags.make
index/CMakeFiles/index.dir/sql.cpp.o: ../index/sql.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object index/CMakeFiles/index.dir/sql.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/index.dir/sql.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/sql.cpp

index/CMakeFiles/index.dir/sql.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index.dir/sql.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/sql.cpp > CMakeFiles/index.dir/sql.cpp.i

index/CMakeFiles/index.dir/sql.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index.dir/sql.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/sql.cpp -o CMakeFiles/index.dir/sql.cpp.s

index/CMakeFiles/index.dir/test.cpp.o: index/CMakeFiles/index.dir/flags.make
index/CMakeFiles/index.dir/test.cpp.o: ../index/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object index/CMakeFiles/index.dir/test.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/index.dir/test.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/test.cpp

index/CMakeFiles/index.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index.dir/test.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/test.cpp > CMakeFiles/index.dir/test.cpp.i

index/CMakeFiles/index.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index.dir/test.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/test.cpp -o CMakeFiles/index.dir/test.cpp.s

index/CMakeFiles/index.dir/z_malloc.cpp.o: index/CMakeFiles/index.dir/flags.make
index/CMakeFiles/index.dir/z_malloc.cpp.o: ../index/z_malloc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object index/CMakeFiles/index.dir/z_malloc.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/index.dir/z_malloc.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/z_malloc.cpp

index/CMakeFiles/index.dir/z_malloc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/index.dir/z_malloc.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/z_malloc.cpp > CMakeFiles/index.dir/z_malloc.cpp.i

index/CMakeFiles/index.dir/z_malloc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/index.dir/z_malloc.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/z_malloc.cpp -o CMakeFiles/index.dir/z_malloc.cpp.s

# Object files for target index
index_OBJECTS = \
"CMakeFiles/index.dir/cprocess.cpp.o" \
"CMakeFiles/index.dir/index_operation.cpp.o" \
"CMakeFiles/index.dir/rb_tree.cpp.o" \
"CMakeFiles/index.dir/skip_list.cpp.o" \
"CMakeFiles/index.dir/sql.cpp.o" \
"CMakeFiles/index.dir/test.cpp.o" \
"CMakeFiles/index.dir/z_malloc.cpp.o"

# External object files for target index
index_EXTERNAL_OBJECTS =

index/libindex.a: index/CMakeFiles/index.dir/cprocess.cpp.o
index/libindex.a: index/CMakeFiles/index.dir/index_operation.cpp.o
index/libindex.a: index/CMakeFiles/index.dir/rb_tree.cpp.o
index/libindex.a: index/CMakeFiles/index.dir/skip_list.cpp.o
index/libindex.a: index/CMakeFiles/index.dir/sql.cpp.o
index/libindex.a: index/CMakeFiles/index.dir/test.cpp.o
index/libindex.a: index/CMakeFiles/index.dir/z_malloc.cpp.o
index/libindex.a: index/CMakeFiles/index.dir/build.make
index/libindex.a: index/CMakeFiles/index.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libindex.a"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && $(CMAKE_COMMAND) -P CMakeFiles/index.dir/cmake_clean_target.cmake
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/index.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
index/CMakeFiles/index.dir/build: index/libindex.a

.PHONY : index/CMakeFiles/index.dir/build

index/CMakeFiles/index.dir/clean:
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index && $(CMAKE_COMMAND) -P CMakeFiles/index.dir/cmake_clean.cmake
.PHONY : index/CMakeFiles/index.dir/clean

index/CMakeFiles/index.dir/depend:
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1 /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/CMakeFiles/index.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : index/CMakeFiles/index.dir/depend

