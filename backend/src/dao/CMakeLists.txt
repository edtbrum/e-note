add_library(lib_dao STATIC cConnectionMySQL.cpp)

target_include_directories(lib_dao PUBLIC ${CMAKE_SOURCE_DIR}/src)

find_library(MYSQL_LIB mysqlcppconn REQUIRED)
target_link_libraries(lib_dao PUBLIC ${MYSQL_LIB})
