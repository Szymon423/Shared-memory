#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "sharedMemory.hpp"

int main(int argc, char **argv)
{
    Action action = Action::UNKNOWN;
    if (argc > 1)
    {
        std::string input = argv[1];
        if (!input.compare("-create"))        action = Action::CREATE;
        else if (!input.compare("-connect"))  action = Action::CONNECT;
    }


    if (action == Action::CREATE)
    {
        std::cout << "Trying to create shared memory: " << SHMEM_NAME << std::endl;
        
        auto pData = static_cast<Data*>(SharedMemory::CreateAndGet(sizeof(Data)));
        if (pData == nullptr) return 0;

        std::cout << "Created shared memory" << std::endl;

        pData->id = 5;
        pData->name[0] = 'c';
        pData->name[1] = 'h';
        pData->name[2] = 'u';
        pData->name[3] = 'j';
        std::cout << "Write to shmm: " << pData->id << " " << pData->name << std::endl;
        std::cout << "Waiting ";
        for (int i = 0; i < 20; i++) 
        {
            std::cout << " ." << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << std::endl << "Closing shared memory: " << SHMEM_NAME << std::endl;
        SharedMemory::Close();
    }
    else if (action == Action::CONNECT)
    {
        std::cout << "Trying to connect to shared memory: " << SHMEM_NAME << std::endl;
        auto pData = static_cast<Data*>(SharedMemory::ConnectAndGet());
        if (pData == nullptr) return 0;
        std::cout << "Read from shmm: " << pData->id << " " << pData->name << std::endl;
    }
    return 0;
}