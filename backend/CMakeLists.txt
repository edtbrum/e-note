cmake_minimum_required(VERSION 3.10.0)
project(e-note VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src/domain)
add_subdirectory(src/dao)
add_subdirectory(src/util)

add_executable(e-note src/main.cpp)

target_include_directories(e-note PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(e-note PRIVATE lib_domain)
target_link_libraries(e-note PRIVATE lib_dao)
target_link_libraries(e-note PRIVATE lib_util)

enable_testing()
add_subdirectory(src/test)
