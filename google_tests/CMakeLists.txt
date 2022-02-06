cmake_minimum_required(VERSION 3.0)
project(pipex C CXX)

find_package(GTest REQUIRED)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SRCS "../works/srcs/**/*.c")
file(GLOB LIBFT "../works/libft/**/*.c")

include_directories("../works/libft/includes")
include_directories("../works/includes")

add_library(pipex
        STATIC
        ${SRCS}
        ${LIBFT}
        ${XSYSCALL}
        ${XLIBFT}
        )

add_executable(main
        main.cpp
        exec_pipex.cpp
        get_fullpath.cpp
        parser.cpp
        validate.cpp
        )

add_definitions(-w)

target_link_libraries(main
    PRIVATE
    GTest::GTest
    GTest::Main
    pipex
)
