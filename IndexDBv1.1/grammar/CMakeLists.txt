aux_source_directory(. grammer)
add_library(grammar ${grammer}
        gammer_tree/gra_tree.cpp gammer_tree/list_fun.cpp
        log/log_fun.cpp word_anylysis/sqlScanner.cpp)
TARGET_LINK_LIBRARIES(grammar index)



