#pragma once

#include <cstddef>

/// @brief Кастомный аллокатор
/// @param size Размер памяти
/// @return Указатель на выделенную память
void* operator new(const size_t size);

/// @brief Кастомный деаллокатор
/// @param ptr Указатель на выделенную память
void operator delete(void* ptr) noexcept;

/// @brief Получит число выделений памяти
/// @return Число выделений памяти
size_t get_allocations();

/// @brief Получит число освобождений памяти
/// @return Число освобождений памяти
size_t get_deallocations();
