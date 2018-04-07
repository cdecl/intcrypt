cmake_minimum_required(VERSION 3.5)

project(libintcrypt)

add_subdirectory(src/test/cpp)
add_subdirectory(src/intcrypt_m)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -O2 -I/usr/local/opt/openssl/include ")

link_directories(/usr/local/opt/openssl/lib)
link_libraries(-lcryptopp -lboost_system -lboost_regex -lssl -lcrypto)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB src "src/*.cpp")
#set(src xxx.cpp)

add_library(intcrypt SHARED ${src})
add_library(intcrypt-static STATIC ${src})
set_target_properties(intcrypt-static PROPERTIES OUTPUT_NAME intcrypt)
