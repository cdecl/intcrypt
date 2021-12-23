cmake_minimum_required(VERSION 3.11)

project(libintcrypt)

if (NOT MSVC)
  add_subdirectory(test/cpp)
  add_subdirectory(test/key_enc)
endif()

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB src "src/*.cpp")

if (NOT MSVC)
  message("-- add_library intcrypt SHARED")
  add_library(intcrypt SHARED ${src})
endif()

message("-- add_library intcrypt-static SHARED")
add_library(intcrypt-static STATIC ${src})
set_target_properties(intcrypt-static PROPERTIES OUTPUT_NAME intcrypt)


if (MSVC)
  target_compile_options(intcrypt-static PRIVATE /MT)
  target_compile_definitions(intcrypt-static PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
  target_compile_options(intcrypt PRIVATE -Wall -O2)
  target_compile_options(intcrypt-static PRIVATE -Wall -O2)
endif()


find_package(cryptopp CONFIG REQUIRED)
if (NOT MSVC)
  target_link_libraries(intcrypt PRIVATE cryptopp-static)
endif()
target_link_libraries(intcrypt-static PRIVATE cryptopp-static)

