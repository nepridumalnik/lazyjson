#pragma once

#include <lazyjson/element.hpp>

#include <vector>
#include <string>

namespace lazyjson
{

/// @brief Массив
class array
{
public:
    /// @brief Конструктор по умолчанию
    array()
    {
    }

    /// @brief Конструктор копирования
    /// @param other Другой экземпляр класса
    array(const array& other)
    {
        operator=(other);
    }

    /// @brief Оператор присваивания
    /// @param other Другой экземпляр класса
    void operator=(const array& other)
    {
        m_vec.reserve(other.m_vec.size());

        for(const auto& e: other.m_vec)
        {
            m_vec.push_back(e);
        }
    }

#pragma region Iterators
    using iterator = std::vector<element>::iterator;
    using const_iterator = std::vector<element>::const_iterator;
    using reverse_iterator = std::vector<element>::reverse_iterator;
    using const_reverse_iterator = std::vector<element>::const_reverse_iterator;

    /// @brief Итератор на начало
    /// @return Итератор
    inline iterator begin()
    {
        return m_vec.begin();
    }

    /// @brief Итератор на конец
    /// @return Итератор
    inline iterator end()
    {
        return m_vec.end();
    }

    /// @brief Итератор на начало
    /// @return Итератор
    inline const_iterator begin() const
    {
        return m_vec.begin();
    }

    /// @brief Итератор на конец
    /// @return Итератор
    inline const_iterator end() const
    {
        return m_vec.end();
    }

    /// @brief Итератор на начало
    /// @return Итератор
    inline const_iterator cbegin() const
    {
        return m_vec.cbegin();
    }

    /// @brief Итератор на конец
    /// @return Итератор
    inline const_iterator cend() const
    {
        return m_vec.cend();
    }

    /// @brief Итератор на начало
    /// @return Итератор
    inline reverse_iterator rbegin()
    {
        return m_vec.rbegin();
    }

    /// @brief Итератор на конец
    /// @return Итератор
    inline reverse_iterator rend()
    {
        return m_vec.rend();
    }

    /// @brief Итератор на начало
    /// @return Итератор
    inline const_reverse_iterator rbegin() const
    {
        return m_vec.rbegin();
    }

    /// @brief Итератор на конец
    /// @return Итератор
    inline const_reverse_iterator rend() const
    {
        return m_vec.rend();
    }

    /// @brief Итератор на начало
    /// @return Итератор
    inline const_reverse_iterator crbegin() const
    {
        return m_vec.crbegin();
    }

    /// @brief Итератор на конец
    /// @return Итератор
    inline const_reverse_iterator crend() const
    {
        return m_vec.crend();
    }

#pragma endregion Iterators

    /// @brief Оператор рандомного доступа
    /// @param index Индекс
    /// @return Элемент
    inline element& operator[](std::size_t index)
    {
        return m_vec[index];
    }

    /// @brief Оператор рандомного доступа
    /// @param index Индекс
    /// @return Элемент
    inline const element& operator[](std::size_t index) const
    {
        return m_vec[index];
    }

    /// @brief Добавить элемент в массив
    /// @param value Элемент
    inline void push_back(const element& value)
    {
        m_vec.push_back(value);
    }

    /// @brief Очистить массив
    inline void clear()
    {
        m_vec.clear();
    }

    /// @brief Проверить пустой ли массив
    /// @return True, если пустой
    inline bool empty() const
    {
        return m_vec.empty();
    }

    /// @brief Удалить крайний объект
    inline void pop_back()
    {
        if(!m_vec.empty())
        {
            m_vec.pop_back();
        }
    }

    /// @brief Получить первый объект
    /// @return Первый элемент
    inline element& front()
    {
        return m_vec.front();
    }

    /// @brief Получить первый объект
    /// @return Первый элемент
    inline const element& front() const
    {
        return m_vec.front();
    }

    /// @brief Получить размер массива
    /// @return Размер массива
    inline std::size_t size() const
    {
        return m_vec.size();
    }

    /// @brief Оператор сравнения
    /// @param other Другой массив
    /// @return True, если равны
    bool operator==(const array& other) const
    {
        if(other.size() != size())
        {
            return false;
        }

        for(size_t i = 0; i < size(); ++i)
        {
            if(m_vec[i] != other.m_vec[i])
            {
                return false;
            }
        }

        return true;
    }

    /// @brief Оператор сравнения
    /// @param other Другой массив
    /// @return True, если не равны
    bool operator!=(const array& other) const
    {
        return !operator==(other);
    }

    /// @brief Приведение типа к строке
    /// @return Строка
    operator std::string() const;

private:
    /// @brief Массив данных
    std::vector<element> m_vec;
};

} // namespace lazyjson