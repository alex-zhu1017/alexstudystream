cmake_minimum_required(VERSION 3.1.0)

project(tcpserver)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_BUILD_TYPE "Debug")

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")

SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

file(GLOB  NET_SOURCE *.cpp)
file(GLOB  NET_HEADER *.h)

add_executable(tcpserver ${NET_SOURCE} ${NET_HEADER})

target_link_libraries(tcpserver
    pthread
)