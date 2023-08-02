#pragma once

#include <lazyjson/variant.hpp>

#include <string>
#include <unordered_map>
#include <string_view>

namespace lazyjson
{

/// @brief Тип значения
using element = variant<int, float, bool, std::string>;

/// @brief JSON объект
class Json
{
public:
    element& operator[](const std::string& key)
    {
        auto& it = obj_.find(key);
        if(it != obj_.end())
        {
            return it->second;
        }

        return obj_[key];
    }

private:
    /// @brief Список в виде ключ/значение
    std::unordered_map<std::string, element> obj_;
};

} // namespace lazyjson
