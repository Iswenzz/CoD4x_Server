add_library(SR)

target_sources(SR PUBLIC main.cpp test.nasm)
target_include_directories(SR PUBLIC .)

get_target_property(SOURCES SR SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
