AUX_SOURCE_DIRECTORY(. POOL)
add_library(custom_pool ${POOL} test.cpp)
TARGET_LINK_LIBRARIES(custom_pool pthread)