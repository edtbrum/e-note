add_library(lib_service STATIC 
    cAutorService.cpp
)

target_include_directories(lib_service PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(lib_service PRIVATE lib_domain)
target_link_libraries(lib_service PRIVATE lib_util)
