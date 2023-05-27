cmake_minimum_required(VERSION 3.17)
project(TimelyDB_V0_1_2)

set(CMAKE_CXX_STANDARD 11)


link_libraries(/usr/local/lib/libyaml.a)


ADD_SUBDIRECTORY(tool)
ADD_SUBDIRECTORY(time_pool)
ADD_SUBDIRECTORY(server)
ADD_SUBDIRECTORY(engine)
ADD_SUBDIRECTORY(filetree)
ADD_SUBDIRECTORY(config_init)

#
#aux_source_directory(./tool tool)
#aux_source_directory(./server server)
#aux_source_directory(./engine engine)
#aux_source_directory(./filetree filetree)
#aux_source_directory(./config_init config_init)
AUX_SOURCE_DIRECTORY(. timelyDb)

add_executable(TimelyDB_V0_1_2 ${timelyDb}  _startup.h time_pool config_init tool server filetree engine)
TARGET_LINK_LIBRARIES(TimelyDB_V0_1_2  pthread  time_pool config_init tool server filetree engine)