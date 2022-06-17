aux_source_directory(. server)
add_library(Server ${server} ser_io_start/server.cpp pack/req_dispose.cpp crc/crc.cpp test/testlab.cpp str/str_fun.cpp)
TARGET_LINK_LIBRARIES(Server pthread boost_system boost_filesystem rt boost_thread)