#pragma once

#include <lazyjson/variant.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace lazyjson
{

/// @brief Предварительное определение
class array;

/// @brief Предварительное определение
class json;

/// @brief Тип значения
using element = variant<int, float, bool, std::string, json, array>;

/// @brief Конвертация в строку
/// @param e Элемент JSON объекта
/// @return Строка
std::string to_string(const element& e);

/// @brief Массив
class array
{
public:
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
    operator std::string() const
    {
        std::string data{"["};

        for(size_t i = 0; i < m_vec.size(); ++i)
        {
            data += to_string(m_vec[i]);

            if(i < (m_vec.size() - 1))
            {
                data += ',';
            }
        }

        data += ']';

        return data;
    }

private:
    /// @brief Массив данных
    std::vector<element> m_vec;
};

/// @brief JSON объект
class json
{
public:
    /// @brief Конструктор по умолчанию
    json() = default;

    /// @brief Конструктор присваивания
    /// @param data Строка
    json(const char* data)
    {
        operator=(data);
    }

    /// @brief Конструктор присваивания
    /// @param data Строка
    json(const std::string& data)
    {
        operator=(data);
    }

    /// @brief Доступ к объекту по ключу
    /// @param key Ключ
    /// @return Значение
    element& operator[](const std::string& key)
    {
        auto& it = m_obj.find(key);
        if(it != m_obj.end())
        {
            return it->second;
        }

        return m_obj[key];
    }

    /// @brief Доступ к объекту по ключу
    /// @param key Ключ
    /// @return Значение
    /// @throw std::out_of_range, если не существует ключ
    const element& operator[](const std::string& key) const
    {
        return m_obj.at(key);
    }

    /// @brief Оператор сравнения
    /// @param other JSON объект
    /// @return True, если равны
    bool operator==(const json& other) const
    {
        if(m_obj.size() != other.m_obj.size())
        {
            return false;
        }

        for(auto this_it = m_obj.begin(), other_it = other.m_obj.begin();
            this_it != m_obj.end() && other_it != other.m_obj.end();
            ++this_it, ++other_it)
        {
            if(this_it->first != other_it->first)
            {
                return false;
            }

            if(this_it->second != other_it->second)
            {
                return false;
            }
        }

        return true;
    }

    /// @brief Оператор сравнения
    /// @param other JSON объект
    /// @return True, если не равны
    bool operator!=(const json& other) const
    {
        return !operator==(other);
    }

    /// @brief Приведение типа к строке
    /// @return Строка
    operator std::string()
    {
        std::string data{"{"};

        for(const auto& e: m_obj)
        {
            data += '"' + e.first + "\":" + to_string(e.second) + ',';
        }

        if(data.size() == 1)
        {
            data += '}';
        }
        else
        {
            data.back() = '}';
        }

        return data;
    }

    /// @brief Приведение строки к JSON
    /// @param data Строка
    void operator=(const char* data)
    {
        operator=(std::string{data});
    }

    /// @brief Приведение строки к JSON
    /// @param data Строка
    void operator=(const std::string& data)
    {
        std::unordered_map<std::string, element> new_obj;

        m_obj.clear();
        m_obj = new_obj;
    }

private:
    /// @brief Список в виде ключ/значение
    std::unordered_map<std::string, element> m_obj;
};

/// @brief Реализация to_string
std::string to_string(const element& e)
{
    if(e.is_type<int>())
    {
        return std::to_string(e.get<int>());
    }
    else if(e.is_type<float>())
    {
        return std::to_string(e.get<float>());
    }
    else if(e.is_type<bool>())
    {
        return e.get<bool>() ? "true" : "false";
    }
    else if(e.is_type<std::string>())
    {
        return '"' + e.get<std::string>() + '"';
    }
    else if(e.is_type<json>())
    {
        return e.get<json>();
    }

    return e.get<array>();
}

} // namespace lazyjson
