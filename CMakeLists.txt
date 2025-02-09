cmake_minimum_required(VERSION 3.14)
project(bandit VERSION 0.1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set up pkg-config to find LZ4
find_package(PkgConfig REQUIRED)
pkg_check_modules(LZ4 REQUIRED liblz4)

# Add library target
add_library(bandit
    src/stream_compressor.cpp
    src/stream_decompressor.cpp
)

# Set include directories for the library
target_include_directories(bandit
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${LZ4_INCLUDE_DIRS}
)

# Link against LZ4
target_link_libraries(bandit PRIVATE ${LZ4_LIBRARIES})

# Add LZ4 library search path for examples
link_directories(${LZ4_LIBRARY_DIRS})

# Add examples subdirectory
add_subdirectory(examples)