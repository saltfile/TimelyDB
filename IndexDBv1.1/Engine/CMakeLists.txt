AUX_SOURCE_DIRECTORY(. DIR_TEST4_SRCS)
add_subdirectory(../snappy snappy)
add_library(Engine ${DIR_TEST4_SRCS})
TARGET_LINK_LIBRARIES(Engine snappy pthread)

