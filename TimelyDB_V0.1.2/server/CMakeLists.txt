AUX_SOURCE_DIRECTORY(. ser)
add_library(server ${ser})
TARGET_LINK_LIBRARIES(server pthread boost_system boost_filesystem rt boost_thread)