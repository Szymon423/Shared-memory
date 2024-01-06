#include "sharedMemory.hpp"
#include <iostream>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>


bip::shared_memory_object SharedMemory::shm;
bip::mapped_region SharedMemory::region;

void* SharedMemory::CreateAndGet(size_t size)
{
    try
    {
        shm = bip::shared_memory_object(bip::open_or_create, SHMEM_NAME, bip::read_write);
        shm.truncate(size);
        region = bip::mapped_region(shm, bip::read_write);
    }
    catch(const bip::interprocess_exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return nullptr;
    }
    NullOut();  

    return region.get_address();
}

void* SharedMemory::ConnectAndGet()
{
    try
    {
        shm = bip::shared_memory_object(bip::open_only, SHMEM_NAME, bip::read_write);
        region = bip::mapped_region(shm, bip::read_write);
    }
    catch (const bip::interprocess_exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return nullptr;
    }
    return region.get_address();
}

void SharedMemory::NullOut()
{
    std::memset(region.get_address(), '\0', region.get_size());
}

void SharedMemory::Close()
{
    bip::shared_memory_object::remove(SHMEM_NAME);
}