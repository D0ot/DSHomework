cmake_minimum_required(VERSION 3.0.0)


add_executable(ch02 test.cc)
target_link_libraries(ch02 gtest_main)
target_include_directories(ch02 PRIVATE ${ROOT_DIR})


