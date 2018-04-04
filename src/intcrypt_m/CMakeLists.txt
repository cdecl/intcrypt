cmake_minimum_required(VERSION 3.5)

project(intcrypt_m)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -O2 -I../")

link_directories(../../)
link_libraries(-lintcrypt)

file(GLOB src "src/*.cpp")
#set(src xxx.cpp)

add_executable(intcrypt_m ${src})
