AUX_SOURCE_DIRECTORY(. config)
add_library(config_init ${config} config_h.h)
TARGET_LINK_LIBRARIES(config_init libxml2)