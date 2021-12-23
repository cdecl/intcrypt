cmake_minimum_required(VERSION 3.5)

project(libintcrypt)

add_subdirectory(test/cpp)
add_subdirectory(test/key_enc)


# set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -O2 -I/usr/local/opt/openssl/include ")
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -O2")

# link_directories(/usr/local/opt/openssl/lib)
# link_libraries(-lcryptopp -lboost_system -lboost_regex -lssl -lcrypto)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB src "src/*.cpp")
#set(src xxx.cpp)

add_library(intcrypt SHARED ${src})
# add_library(intcrypt-static STATIC ${src})
# set_target_properties(intcrypt-static PROPERTIES OUTPUT_NAME intcrypt)

# target_include_directories(intcrypt PRIVATE /home/cdecl/lib/vcpkg/installed/x64-linux/include/)
# target_include_directories(intcrypt-static PRIVATE /home/cdecl/lib/vcpkg/installed/x64-linux/include/)

# find_package(Boost REQUIRED COMPONENTS algorithm)
# target_link_libraries(intcrypt INTERFACE Boost::boost)

find_package(cryptopp CONFIG REQUIRED)
target_link_libraries(intcrypt PRIVATE cryptopp-static)
# target_link_libraries(intcrypt-static PRIVATE cryptopp-static)

