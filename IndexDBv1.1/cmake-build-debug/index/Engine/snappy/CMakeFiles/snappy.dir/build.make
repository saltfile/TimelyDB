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
CMAKE_COMMAND = /opt/IDE/CLion-2020.2.5/clion-2020.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/IDE/CLion-2020.2.5/clion-2020.2.5/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /opt/git_Pro/indexDb/IndexDBv1.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug

# Include any dependencies generated for this target.
include index/Engine/snappy/CMakeFiles/snappy.dir/depend.make

# Include the progress variables for this target.
include index/Engine/snappy/CMakeFiles/snappy.dir/progress.make

# Include the compile flags for this target's objects.
include index/Engine/snappy/CMakeFiles/snappy.dir/flags.make

index/Engine/snappy/CMakeFiles/snappy.dir/snappy-c.cc.o: index/Engine/snappy/CMakeFiles/snappy.dir/flags.make
index/Engine/snappy/CMakeFiles/snappy.dir/snappy-c.cc.o: ../snappy/snappy-c.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object index/Engine/snappy/CMakeFiles/snappy.dir/snappy-c.cc.o"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/snappy.dir/snappy-c.cc.o -c /opt/git_Pro/indexDb/IndexDBv1.1/snappy/snappy-c.cc

index/Engine/snappy/CMakeFiles/snappy.dir/snappy-c.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/snappy.dir/snappy-c.cc.i"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/git_Pro/indexDb/IndexDBv1.1/snappy/snappy-c.cc > CMakeFiles/snappy.dir/snappy-c.cc.i

index/Engine/snappy/CMakeFiles/snappy.dir/snappy-c.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/snappy.dir/snappy-c.cc.s"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/git_Pro/indexDb/IndexDBv1.1/snappy/snappy-c.cc -o CMakeFiles/snappy.dir/snappy-c.cc.s

index/Engine/snappy/CMakeFiles/snappy.dir/snappy-sinksource.cc.o: index/Engine/snappy/CMakeFiles/snappy.dir/flags.make
index/Engine/snappy/CMakeFiles/snappy.dir/snappy-sinksource.cc.o: ../snappy/snappy-sinksource.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object index/Engine/snappy/CMakeFiles/snappy.dir/snappy-sinksource.cc.o"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/snappy.dir/snappy-sinksource.cc.o -c /opt/git_Pro/indexDb/IndexDBv1.1/snappy/snappy-sinksource.cc

index/Engine/snappy/CMakeFiles/snappy.dir/snappy-sinksource.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/snappy.dir/snappy-sinksource.cc.i"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/git_Pro/indexDb/IndexDBv1.1/snappy/snappy-sinksource.cc > CMakeFiles/snappy.dir/snappy-sinksource.cc.i

index/Engine/snappy/CMakeFiles/snappy.dir/snappy-sinksource.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/snappy.dir/snappy-sinksource.cc.s"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/git_Pro/indexDb/IndexDBv1.1/snappy/snappy-sinksource.cc -o CMakeFiles/snappy.dir/snappy-sinksource.cc.s

index/Engine/snappy/CMakeFiles/snappy.dir/snappy-stubs-internal.cc.o: index/Engine/snappy/CMakeFiles/snappy.dir/flags.make
index/Engine/snappy/CMakeFiles/snappy.dir/snappy-stubs-internal.cc.o: ../snappy/snappy-stubs-internal.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object index/Engine/snappy/CMakeFiles/snappy.dir/snappy-stubs-internal.cc.o"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/snappy.dir/snappy-stubs-internal.cc.o -c /opt/git_Pro/indexDb/IndexDBv1.1/snappy/snappy-stubs-internal.cc

index/Engine/snappy/CMakeFiles/snappy.dir/snappy-stubs-internal.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/snappy.dir/snappy-stubs-internal.cc.i"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/git_Pro/indexDb/IndexDBv1.1/snappy/snappy-stubs-internal.cc > CMakeFiles/snappy.dir/snappy-stubs-internal.cc.i

index/Engine/snappy/CMakeFiles/snappy.dir/snappy-stubs-internal.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/snappy.dir/snappy-stubs-internal.cc.s"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/git_Pro/indexDb/IndexDBv1.1/snappy/snappy-stubs-internal.cc -o CMakeFiles/snappy.dir/snappy-stubs-internal.cc.s

index/Engine/snappy/CMakeFiles/snappy.dir/snappy.cc.o: index/Engine/snappy/CMakeFiles/snappy.dir/flags.make
index/Engine/snappy/CMakeFiles/snappy.dir/snappy.cc.o: ../snappy/snappy.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object index/Engine/snappy/CMakeFiles/snappy.dir/snappy.cc.o"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/snappy.dir/snappy.cc.o -c /opt/git_Pro/indexDb/IndexDBv1.1/snappy/snappy.cc

index/Engine/snappy/CMakeFiles/snappy.dir/snappy.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/snappy.dir/snappy.cc.i"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/git_Pro/indexDb/IndexDBv1.1/snappy/snappy.cc > CMakeFiles/snappy.dir/snappy.cc.i

index/Engine/snappy/CMakeFiles/snappy.dir/snappy.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/snappy.dir/snappy.cc.s"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/git_Pro/indexDb/IndexDBv1.1/snappy/snappy.cc -o CMakeFiles/snappy.dir/snappy.cc.s

# Object files for target snappy
snappy_OBJECTS = \
"CMakeFiles/snappy.dir/snappy-c.cc.o" \
"CMakeFiles/snappy.dir/snappy-sinksource.cc.o" \
"CMakeFiles/snappy.dir/snappy-stubs-internal.cc.o" \
"CMakeFiles/snappy.dir/snappy.cc.o"

# External object files for target snappy
snappy_EXTERNAL_OBJECTS =

index/Engine/snappy/libsnappy.a: index/Engine/snappy/CMakeFiles/snappy.dir/snappy-c.cc.o
index/Engine/snappy/libsnappy.a: index/Engine/snappy/CMakeFiles/snappy.dir/snappy-sinksource.cc.o
index/Engine/snappy/libsnappy.a: index/Engine/snappy/CMakeFiles/snappy.dir/snappy-stubs-internal.cc.o
index/Engine/snappy/libsnappy.a: index/Engine/snappy/CMakeFiles/snappy.dir/snappy.cc.o
index/Engine/snappy/libsnappy.a: index/Engine/snappy/CMakeFiles/snappy.dir/build.make
index/Engine/snappy/libsnappy.a: index/Engine/snappy/CMakeFiles/snappy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libsnappy.a"
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && $(CMAKE_COMMAND) -P CMakeFiles/snappy.dir/cmake_clean_target.cmake
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/snappy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
index/Engine/snappy/CMakeFiles/snappy.dir/build: index/Engine/snappy/libsnappy.a

.PHONY : index/Engine/snappy/CMakeFiles/snappy.dir/build

index/Engine/snappy/CMakeFiles/snappy.dir/clean:
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy && $(CMAKE_COMMAND) -P CMakeFiles/snappy.dir/cmake_clean.cmake
.PHONY : index/Engine/snappy/CMakeFiles/snappy.dir/clean

index/Engine/snappy/CMakeFiles/snappy.dir/depend:
	cd /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/git_Pro/indexDb/IndexDBv1.1 /opt/git_Pro/indexDb/IndexDBv1.1/snappy /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy /opt/git_Pro/indexDb/IndexDBv1.1/cmake-build-debug/index/Engine/snappy/CMakeFiles/snappy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : index/Engine/snappy/CMakeFiles/snappy.dir/depend

