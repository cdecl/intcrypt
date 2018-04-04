cmake_minimum_required(VERSION 3.5)

project(libintcrypt)

add_subdirectory(src/test/cpp)
add_subdirectory(src/intcrypt_m)


set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -O2 -I/usr/local/opt/openssl/include ")

link_directories(/usr/local/opt/openssl/lib)
link_libraries(-lcryptopp -lboost_system -lboost_regex -lssl -lcrypto)

file(GLOB src "src/*.cpp")
#set(src xxx.cpp)

#add_library(intcrypt STATIC ${src})
add_library(intcrypt SHARED ${src})

