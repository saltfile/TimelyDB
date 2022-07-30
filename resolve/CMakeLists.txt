cmake_minimum_required(VERSION 3.17)
project(resolve)

set(CMAKE_CXX_STANDARD 14)

add_executable(resolve main.cpp Myall.h word_anylysis/sqlScanner.cpp gammer_tree/gra_tree.cpp gammer_tree/list_fun.cpp log/log_fun.cpp
        global_c.h database_engine.h vfsTree.cpp)