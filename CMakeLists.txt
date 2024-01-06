cmake_minimum_required(VERSION 3.1)

project(shmem VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CPP_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

add_subdirectory(SharedMemory)

add_executable(shmem main.cpp)

target_link_libraries(shmem PUBLIC shmemlib)