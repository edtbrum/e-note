add_library(lib_controller STATIC 
    autorController.cpp
)

target_include_directories(lib_controller PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(lib_controller PRIVATE lib_domain)
target_link_libraries(lib_controller PRIVATE lib_util)
target_link_libraries(lib_controller PRIVATE lib_service)
