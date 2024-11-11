cmake_minimum_required(VERSION 3.29)
project(fibonacciHeap)

set(CMAKE_CXX_STANDARD 23)

add_executable(fibonacciHeap
        main.cpp
)

add_subdirectory(src)

target_include_directories(fibonacciHeap PRIVATE .)
target_link_libraries(fibonacciHeap
        PRIVATE fibHeap)
