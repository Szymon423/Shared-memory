#pragma once

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

#define shared_memory_name "sharedmemory"

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
    Data* pData;
    bip::shared_memory_object shm;
    bip::mapped_region region;

public:
    SharedMemory();
    ~SharedMemory();
    
    bool Create();
    bool Connect();
    Data* GetSharedMemory();
};