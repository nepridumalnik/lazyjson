#pragma once

#include <lazyjson/variant.hpp>
#include <lazyjson/element.hpp>
#include <lazyjson/json.hpp>
#include <lazyjson/array.hpp>

#include <string>

namespace lazyjson
{

/// @brief Конвертация в строку
/// @param e Элемент JSON объекта
/// @return Строка
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

json::operator std::string()
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

array::operator std::string() const
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

} // namespace lazyjson