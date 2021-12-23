## Intcrypt 
- Cryptopp 사용 암호화 모듈 (Shared/Static)

### Build 

#### vcpkg 

```sh
$ ./vcpkg 
./vcpkg install cryptopp boost-algorithm
Computing installation plan...
The following packages are already installed:
    boost-algorithm[core]:x64-linux -> 1.76.0
    cryptopp[core]:x64-linux -> 8.5.0
Package boost-algorithm:x64-linux is already installed
Package cryptopp:x64-linux is already installed

Total elapsed time: 44.9 us

The package boost is compatible with built-in CMake targets:

    find_package(Boost REQUIRED [COMPONENTS <libs>...])
    target_link_libraries(main PRIVATE Boost::boost Boost::<lib1> Boost::<lib2> ...)

The package cryptopp:x64-linux provides CMake targets:

    find_package(cryptopp CONFIG REQUIRED)
    target_link_libraries(main PRIVATE cryptopp-static)
```

```sh
# CMake Init
$ cmake -B build -DCMAKE_TOOLCHAIN_FILE=~/lib/vcpkg/scripts/buildsystems/vcpkg.cmake
-- The C compiler identification is GNU 9.3.0
-- The CXX compiler identification is GNU 9.3.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/cdecl/temp/intcrypt/build

# Build
$ cmake --build build 
...


$ tree build/lib
build/lib
├── libintcrypt.a
└── libintcrypt.so

# Test
$ build/bin/test
===============================================================================
All tests passed (10 assertions in 1 test case)
...
```

#### Windows 
