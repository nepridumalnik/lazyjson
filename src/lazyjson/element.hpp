#pragma once

#include <lazyjson/variant.hpp>

#include <string>

namespace lazyjson
{

/// @brief Предварительное определение
class json;

/// @brief Предварительное определение
class array;

/// @brief Тип значения
using element = variant<int, float, bool, std::string, json, array>;

} // namespace lazyjson