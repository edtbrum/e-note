add_library(lib_domain STATIC 
    cAutor.cpp
    cNota.cpp
    cTag.cpp
    cNotaTag.cpp
)

target_include_directories(lib_domain PUBLIC ${CMAKE_SOURCE_DIR}/src)
