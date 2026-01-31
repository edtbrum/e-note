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

# Teste de acesso à tabela nota
add_executable(test_cNotaDAO test_cNotaDAO.cpp)
target_include_directories(test_cNotaDAO PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_cNotaDAO PRIVATE lib_domain)
target_link_libraries(test_cNotaDAO PRIVATE lib_dao)
target_link_libraries(test_cNotaDAO PRIVATE lib_util)
add_test(NAME tb_nota COMMAND test_cNotaDAO)

# Teste dos serviços da classe cAutorService
add_executable(test_cAutorService test_cAutorService.cpp)
target_include_directories(test_cAutorService PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_cAutorService PRIVATE lib_domain)
target_link_libraries(test_cAutorService PRIVATE lib_util)
target_link_libraries(test_cAutorService PRIVATE lib_dao)
target_link_libraries(test_cAutorService PRIVATE lib_service)
add_test(NAME service_autor COMMAND test_cAutorService)
