add_library(lib_dao STATIC cConnectionMySQL.cpp)

target_include_directories(lib_domain PUBLIC ${CMAKE_SOURCE_DIR}/src)
