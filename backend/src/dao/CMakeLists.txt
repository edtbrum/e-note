add_library(lib_dao STATIC 
    cConnectionMySQL.cpp
    cAutorDAO.cpp
    cNotaDAO.cpp
    cLembreteDAO.cpp
    cTagDAO.cpp
)

target_include_directories(lib_dao PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(lib_dao PRIVATE lib_domain)
target_link_libraries(lib_dao PRIVATE lib_util)

find_library(MYSQL_LIB mysqlcppconn REQUIRED)
target_link_libraries(lib_dao PUBLIC ${MYSQL_LIB})
