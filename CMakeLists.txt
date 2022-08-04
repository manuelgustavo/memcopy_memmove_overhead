cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(benchmark REQUIRED)

add_executable(main main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
