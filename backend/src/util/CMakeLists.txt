add_library(lib_util STATIC 
    uTimePoint.cpp
)

target_include_directories(lib_util PUBLIC ${CMAKE_SOURCE_DIR}/src)
