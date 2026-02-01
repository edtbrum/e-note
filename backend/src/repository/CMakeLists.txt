add_library(lib_repository STATIC 
    cNotaRepository.cpp
)

target_include_directories(lib_repository PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(lib_repository PUBLIC ${CMAKE_SOURCE_DIR}/src/repository)

target_link_libraries(lib_repository PRIVATE lib_domain)
target_link_libraries(lib_repository PRIVATE lib_util)
target_link_libraries(lib_repository PRIVATE lib_dao)
