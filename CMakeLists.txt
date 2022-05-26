cmake_minimum_required(VERSION 3.15.5)
SET(CMAKE_CXX_STANDARD 17)
project(Encrypt CXX)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(run ${SOURCES})

