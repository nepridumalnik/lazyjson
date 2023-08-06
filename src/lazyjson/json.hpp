#pragma once

#include <lazyjson/element.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace lazyjson
{

/// @brief JSON объект
class json
{
public:
    /// @brief Конструктор по умолчанию
    json(){};

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
        const auto& it = m_obj.find(key);
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
    operator std::string();

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

} // namespace lazyjson
