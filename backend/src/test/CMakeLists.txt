# Teste de conexão com o banco de dados
add_executable(test_connectionMySQL test_connectionMySQL.cpp)
target_include_directories(test_connectionMySQL PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_connectionMySQL PRIVATE lib_dao)
add_test(NAME db_connection COMMAND test_connectionMySQL)

# Teste de acesso à tabela autor
add_executable(test_cAutorDAO test_cAutorDAO.cpp)
target_include_directories(test_cAutorDAO PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_cAutorDAO PRIVATE lib_domain)
target_link_libraries(test_cAutorDAO PRIVATE lib_dao)
add_test(NAME tb_autor COMMAND test_cAutorDAO)
