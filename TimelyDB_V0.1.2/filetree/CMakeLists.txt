AUX_SOURCE_DIRECTORY(. ftree)

file(GLOB_RECURSE SOURCES "token/*.cpp" "lexer/*.cpp" "json/*.cpp" "ast/*.cpp"
        "parser/*.cpp" )


add_library(filetree ${ftree} ${SOURCES})