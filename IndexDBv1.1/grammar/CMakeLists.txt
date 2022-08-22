aux_source_directory(. grammer)
add_library(grammar ${grammer}
        gammer_tree/gra_tree.cpp gammer_tree/list_fun.cpp
        word_anylysis/sqlScanner.cpp
        log/log_fun.cpp)