cmake_minimum_required(VERSION 3.17)
project(TimelyDB_V0_1_2)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(config_init)
add_subdirectory(tool)
add_subdirectory(server)
add_subdirectory(engine)
add_subdirectory(filetree)

aux_source_directory(./config_init config_init)
aux_source_directory(./tool tool)
aux_source_directory(./server server)
aux_source_directory(./engine engine)
aux_source_directory(./filetree filetree)
aux_source_directory(. timelyDb)

add_executable(TimelyDB_V0_1_2 ${timelyDb})
TARGET_LINK_LIBRARIES(TimelyDB_V0_1_2  pthread libxml2)