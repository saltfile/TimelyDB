cmake_minimum_required(VERSION 3.17)
project(IndexDBv1_1)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(grammar)
add_subdirectory(Server)
#add_subdirectory(Engine)
add_subdirectory(index)
add_subdirectory(custom_pool)
#add_subdirectory(primitive)

aux_source_directory(./grammar grammar)
aux_source_directory(./Server Server)
aux_source_directory(./custom_pool custom_pool)
#aux_source_directory(./Engine Engine)
aux_source_directory(./index index)
#aux_source_directory(./primitive primitive)
AUX_SOURCE_DIRECTORY(. indexDB)
add_executable(IndexDBv1_1  ${indexDB} )
TARGET_LINK_LIBRARIES(IndexDBv1_1  grammar Server custom_pool Engine index  pthread)


