cmake_minimum_required(VERSION 3.17)
project(TimelyDB_V0_1_2)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(tool)

aux_source_directory(./tool tool)


aux_source_directory(. timelyDb)

add_executable(TimelyDB_V0_1_2 ${timelyDb} tool/str_tool.cpp)
TARGET_LINK_LIBRARIES(TimelyDB_V0_1_2  tool  pthread)