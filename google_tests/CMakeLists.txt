cmake_minimum_required(VERSION 3.0)
project(pipex C CXX)

find_package(GTest REQUIRED)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SRCS "../works/srcs/*.c")
file(GLOB LIBFT "../works/libft/*.c")
file(GLOB XSYSCALL "../works/srcs/xsyscall/*.c")

include_directories("../works/libft")
include_directories("../works/includes")

add_library(pipex
  STATIC
  ${SRCS}
  ${LIBFT}
  ${XSYSCALL}
)

add_executable(main main.cpp)

add_definitions(-w)

target_link_libraries(main
    PRIVATE
    GTest::GTest
    GTest::Main
    pipex
)