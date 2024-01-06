#pragma once

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

#define SHMEM_NAME "MySharedMemory"

namespace bip = boost::interprocess;

struct Data
{
    int id;
    char name[10];
};

enum class Action
{
    CREATE,
    CONNECT,
    UNKNOWN
};

class SharedMemory
{
private:
    static bip::shared_memory_object shm;
    static bip::mapped_region region;

public:
    SharedMemory() = delete;
    ~SharedMemory() = delete;
    SharedMemory(SharedMemory&) = delete;
    SharedMemory(SharedMemory&&) = delete;

    static void* CreateAndGet(size_t size);
    static void* ConnectAndGet();
    static void NullOut();
    static void Close();
};