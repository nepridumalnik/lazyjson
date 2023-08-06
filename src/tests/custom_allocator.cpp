#include <tests/custom_allocator.hpp>

#include <cstdlib>

/// @brief Счётчик выделений памяти
size_t allocations_counter = 0;

/// @brief Счётчик освобождений памяти
size_t deallocations_counter = 0;

void* operator new(const size_t size)
{
    ++allocations_counter;
    return malloc(size);
}

void operator delete(void* ptr)
{
    ++deallocations_counter;
    free(ptr);
}

size_t get_allocations()
{
    return allocations_counter;
}

size_t get_deallocations()
{
    return deallocations_counter;
}