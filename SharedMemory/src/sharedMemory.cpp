#include "sharedMemory.hpp"
#include <iostream>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>


SharedMemory::SharedMemory() : shm(), region()
{
    // bip::shared_memory_object::remove(shared_memory_name);
}

SharedMemory::~SharedMemory()
{
    bip::shared_memory_object::remove(shared_memory_name);
}

bool SharedMemory::Create()
{
    try
    {
        shm = bip::shared_memory_object(bip::create_only, shared_memory_name, bip::read_write);
        shm.truncate(sizeof(Data));
        region = bip::mapped_region(shm, bip::read_write);
    }
    catch(const bip::interprocess_exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return false;
    }
    std::memset(region.get_address(), '\0', region.get_size());

    return true;
}

bool SharedMemory::Connect()
{
    try
    {
        shm = bip::shared_memory_object(bip::open_only, shared_memory_name, bip::read_write);
    }
    catch(const bip::interprocess_exception& ex)
    {
        std::cout << "shared_memory_object error: " << ex.what() << std::endl;
        return false;
    }

    try
    {
        region = bip::mapped_region(shm, bip::read_write);
    }
    catch(const bip::interprocess_exception& ex)
    {
        std::cout << "mapped_region error: " << ex.what() << std::endl;
        return false;
    }
    return true;
}

Data* SharedMemory::GetSharedMemory()
{
    return static_cast<Data*>(region.get_address());;
}