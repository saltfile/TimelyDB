AUX_SOURCE_DIRECTORY(. server)
add_executable(Server ${server} ser_drive.h crc/crc.cpp pack/req_dispose.cpp ser_io_start/server.cpp test/testlab.cpp)
