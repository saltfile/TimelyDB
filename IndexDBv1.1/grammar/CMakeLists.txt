AUX_SOURCE_DIRECTORY(. GRA)
add_library(grammar ${GRA} gammer_tree/gra_tree.cpp gammer_tree/list_fun.cpp log/log_fun.cpp word_anylysis/sqlScanner.cpp)