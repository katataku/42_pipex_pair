cmake_minimum_required(VERSION 3.0)
project(pipex C CXX)

find_package(GTest REQUIRED)
set(CMAKE_CXX_STANDARD 17)

file(GLOB LIBFT "../works/libft/*.c")

add_library(pipex
  STATIC
  ../works/pipex.c
  ${LIBFT}
)

add_executable(main main.cpp)

add_definitions(-w)

target_link_libraries(main
    PRIVATE
    GTest::GTest
    GTest::Main
    pipex
)