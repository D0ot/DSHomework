cmake_minimum_required(VERSION 3.0.0)
project(DSHomeWork VERSION 0.1.0)


set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${ROOT_DIR}/general)

add_subdirectory(googletest)
add_subdirectory(ch02)
add_subdirectory(ch02exp)
add_subdirectory(ch03)
add_subdirectory(ch03exp)
add_subdirectory(ch05exp)

add_executable(DSHomeWork main.cpp)
target_compile_options(DSHomeWork PRIVATE -g -Wall -Wextra)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
