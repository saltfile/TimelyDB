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
include index/Engine/CMakeFiles/Engine.dir/depend.make

# Include the progress variables for this target.
include index/Engine/CMakeFiles/Engine.dir/progress.make

# Include the compile flags for this target's objects.
include index/Engine/CMakeFiles/Engine.dir/flags.make

index/Engine/CMakeFiles/Engine.dir/circularList.cpp.o: index/Engine/CMakeFiles/Engine.dir/flags.make
index/Engine/CMakeFiles/Engine.dir/circularList.cpp.o: ../Engine/circularList.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object index/Engine/CMakeFiles/Engine.dir/circularList.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/circularList.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/circularList.cpp

index/Engine/CMakeFiles/Engine.dir/circularList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/circularList.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/circularList.cpp > CMakeFiles/Engine.dir/circularList.cpp.i

index/Engine/CMakeFiles/Engine.dir/circularList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/circularList.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/circularList.cpp -o CMakeFiles/Engine.dir/circularList.cpp.s

index/Engine/CMakeFiles/Engine.dir/engine.cpp.o: index/Engine/CMakeFiles/Engine.dir/flags.make
index/Engine/CMakeFiles/Engine.dir/engine.cpp.o: ../Engine/engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object index/Engine/CMakeFiles/Engine.dir/engine.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/engine.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/engine.cpp

index/Engine/CMakeFiles/Engine.dir/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/engine.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/engine.cpp > CMakeFiles/Engine.dir/engine.cpp.i

index/Engine/CMakeFiles/Engine.dir/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/engine.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/engine.cpp -o CMakeFiles/Engine.dir/engine.cpp.s

index/Engine/CMakeFiles/Engine.dir/loaddisk.cpp.o: index/Engine/CMakeFiles/Engine.dir/flags.make
index/Engine/CMakeFiles/Engine.dir/loaddisk.cpp.o: ../Engine/loaddisk.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object index/Engine/CMakeFiles/Engine.dir/loaddisk.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/loaddisk.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/loaddisk.cpp

index/Engine/CMakeFiles/Engine.dir/loaddisk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/loaddisk.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/loaddisk.cpp > CMakeFiles/Engine.dir/loaddisk.cpp.i

index/Engine/CMakeFiles/Engine.dir/loaddisk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/loaddisk.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/loaddisk.cpp -o CMakeFiles/Engine.dir/loaddisk.cpp.s

index/Engine/CMakeFiles/Engine.dir/ops.cpp.o: index/Engine/CMakeFiles/Engine.dir/flags.make
index/Engine/CMakeFiles/Engine.dir/ops.cpp.o: ../Engine/ops.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object index/Engine/CMakeFiles/Engine.dir/ops.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/ops.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/ops.cpp

index/Engine/CMakeFiles/Engine.dir/ops.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/ops.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/ops.cpp > CMakeFiles/Engine.dir/ops.cpp.i

index/Engine/CMakeFiles/Engine.dir/ops.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/ops.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/ops.cpp -o CMakeFiles/Engine.dir/ops.cpp.s

index/Engine/CMakeFiles/Engine.dir/pthread_myrwlock.cpp.o: index/Engine/CMakeFiles/Engine.dir/flags.make
index/Engine/CMakeFiles/Engine.dir/pthread_myrwlock.cpp.o: ../Engine/pthread_myrwlock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object index/Engine/CMakeFiles/Engine.dir/pthread_myrwlock.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/pthread_myrwlock.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/pthread_myrwlock.cpp

index/Engine/CMakeFiles/Engine.dir/pthread_myrwlock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/pthread_myrwlock.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/pthread_myrwlock.cpp > CMakeFiles/Engine.dir/pthread_myrwlock.cpp.i

index/Engine/CMakeFiles/Engine.dir/pthread_myrwlock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/pthread_myrwlock.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/pthread_myrwlock.cpp -o CMakeFiles/Engine.dir/pthread_myrwlock.cpp.s

index/Engine/CMakeFiles/Engine.dir/test.cpp.o: index/Engine/CMakeFiles/Engine.dir/flags.make
index/Engine/CMakeFiles/Engine.dir/test.cpp.o: ../Engine/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object index/Engine/CMakeFiles/Engine.dir/test.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/test.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/test.cpp

index/Engine/CMakeFiles/Engine.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/test.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/test.cpp > CMakeFiles/Engine.dir/test.cpp.i

index/Engine/CMakeFiles/Engine.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/test.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/test.cpp -o CMakeFiles/Engine.dir/test.cpp.s

index/Engine/CMakeFiles/Engine.dir/vfsTree.cpp.o: index/Engine/CMakeFiles/Engine.dir/flags.make
index/Engine/CMakeFiles/Engine.dir/vfsTree.cpp.o: ../Engine/vfsTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object index/Engine/CMakeFiles/Engine.dir/vfsTree.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/vfsTree.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/vfsTree.cpp

index/Engine/CMakeFiles/Engine.dir/vfsTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/vfsTree.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/vfsTree.cpp > CMakeFiles/Engine.dir/vfsTree.cpp.i

index/Engine/CMakeFiles/Engine.dir/vfsTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/vfsTree.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/vfsTree.cpp -o CMakeFiles/Engine.dir/vfsTree.cpp.s

index/Engine/CMakeFiles/Engine.dir/wal.cpp.o: index/Engine/CMakeFiles/Engine.dir/flags.make
index/Engine/CMakeFiles/Engine.dir/wal.cpp.o: ../Engine/wal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object index/Engine/CMakeFiles/Engine.dir/wal.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/wal.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/wal.cpp

index/Engine/CMakeFiles/Engine.dir/wal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/wal.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/wal.cpp > CMakeFiles/Engine.dir/wal.cpp.i

index/Engine/CMakeFiles/Engine.dir/wal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/wal.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine/wal.cpp -o CMakeFiles/Engine.dir/wal.cpp.s

index/Engine/CMakeFiles/Engine.dir/__/index/skip_list.cpp.o: index/Engine/CMakeFiles/Engine.dir/flags.make
index/Engine/CMakeFiles/Engine.dir/__/index/skip_list.cpp.o: ../index/skip_list.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object index/Engine/CMakeFiles/Engine.dir/__/index/skip_list.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/__/index/skip_list.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/skip_list.cpp

index/Engine/CMakeFiles/Engine.dir/__/index/skip_list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/__/index/skip_list.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/skip_list.cpp > CMakeFiles/Engine.dir/__/index/skip_list.cpp.i

index/Engine/CMakeFiles/Engine.dir/__/index/skip_list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/__/index/skip_list.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/skip_list.cpp -o CMakeFiles/Engine.dir/__/index/skip_list.cpp.s

index/Engine/CMakeFiles/Engine.dir/__/index/z_malloc.cpp.o: index/Engine/CMakeFiles/Engine.dir/flags.make
index/Engine/CMakeFiles/Engine.dir/__/index/z_malloc.cpp.o: ../index/z_malloc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object index/Engine/CMakeFiles/Engine.dir/__/index/z_malloc.cpp.o"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Engine.dir/__/index/z_malloc.cpp.o -c /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/z_malloc.cpp

index/Engine/CMakeFiles/Engine.dir/__/index/z_malloc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Engine.dir/__/index/z_malloc.cpp.i"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/z_malloc.cpp > CMakeFiles/Engine.dir/__/index/z_malloc.cpp.i

index/Engine/CMakeFiles/Engine.dir/__/index/z_malloc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Engine.dir/__/index/z_malloc.cpp.s"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/index/z_malloc.cpp -o CMakeFiles/Engine.dir/__/index/z_malloc.cpp.s

# Object files for target Engine
Engine_OBJECTS = \
"CMakeFiles/Engine.dir/circularList.cpp.o" \
"CMakeFiles/Engine.dir/engine.cpp.o" \
"CMakeFiles/Engine.dir/loaddisk.cpp.o" \
"CMakeFiles/Engine.dir/ops.cpp.o" \
"CMakeFiles/Engine.dir/pthread_myrwlock.cpp.o" \
"CMakeFiles/Engine.dir/test.cpp.o" \
"CMakeFiles/Engine.dir/vfsTree.cpp.o" \
"CMakeFiles/Engine.dir/wal.cpp.o" \
"CMakeFiles/Engine.dir/__/index/skip_list.cpp.o" \
"CMakeFiles/Engine.dir/__/index/z_malloc.cpp.o"

# External object files for target Engine
Engine_EXTERNAL_OBJECTS =

index/Engine/libEngine.a: index/Engine/CMakeFiles/Engine.dir/circularList.cpp.o
index/Engine/libEngine.a: index/Engine/CMakeFiles/Engine.dir/engine.cpp.o
index/Engine/libEngine.a: index/Engine/CMakeFiles/Engine.dir/loaddisk.cpp.o
index/Engine/libEngine.a: index/Engine/CMakeFiles/Engine.dir/ops.cpp.o
index/Engine/libEngine.a: index/Engine/CMakeFiles/Engine.dir/pthread_myrwlock.cpp.o
index/Engine/libEngine.a: index/Engine/CMakeFiles/Engine.dir/test.cpp.o
index/Engine/libEngine.a: index/Engine/CMakeFiles/Engine.dir/vfsTree.cpp.o
index/Engine/libEngine.a: index/Engine/CMakeFiles/Engine.dir/wal.cpp.o
index/Engine/libEngine.a: index/Engine/CMakeFiles/Engine.dir/__/index/skip_list.cpp.o
index/Engine/libEngine.a: index/Engine/CMakeFiles/Engine.dir/__/index/z_malloc.cpp.o
index/Engine/libEngine.a: index/Engine/CMakeFiles/Engine.dir/build.make
index/Engine/libEngine.a: index/Engine/CMakeFiles/Engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX static library libEngine.a"
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && $(CMAKE_COMMAND) -P CMakeFiles/Engine.dir/cmake_clean_target.cmake
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
index/Engine/CMakeFiles/Engine.dir/build: index/Engine/libEngine.a

.PHONY : index/Engine/CMakeFiles/Engine.dir/build

index/Engine/CMakeFiles/Engine.dir/clean:
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine && $(CMAKE_COMMAND) -P CMakeFiles/Engine.dir/cmake_clean.cmake
.PHONY : index/Engine/CMakeFiles/Engine.dir/clean

index/Engine/CMakeFiles/Engine.dir/depend:
	cd /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1 /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/Engine /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine /home/saltfish/下载/新/xin/indexTSDB/IndexDBv1.1/cmake-build-debug/index/Engine/CMakeFiles/Engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : index/Engine/CMakeFiles/Engine.dir/depend

