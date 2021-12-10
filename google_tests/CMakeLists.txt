cmake_minimum_required(VERSION 3.0)
project(cmake_example C CXX)

find_package(GTest REQUIRED)
set(CMAKE_CXX_STANDARD 17)

# cpc03の場合の例
# add_library(ex00 STATIC ../works/ex00/ft_strlen.c)

add_executable(main main.cpp)

target_link_libraries(main
  PRIVATE
    GTest::GTest
    GTest::Main
#    ex00
)