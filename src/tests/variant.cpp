#include <lazyjson/variant.hpp>

#include <gtest/gtest.h>

#include <string>

namespace json = lazyjson;

/// @brief Создать класс одного типа и положить в него значение другого типа
/// @tparam Ta первый тип
/// @tparam Tb второй тип
/// @param value значение
template<typename Ta, typename Tb>
void CreateVar(const Tb value)
{
    json::variant<Ta> var{value};
}

// Создание
TEST(VariantUsage, CreationOk)
{
    ASSERT_NO_THROW((CreateVar<int, int>(int{})));
    ASSERT_NO_THROW((CreateVar<size_t, size_t>(size_t{})));
    ASSERT_NO_THROW((CreateVar<bool, bool>(bool{})));
}

// Создание с неверным типом
TEST(VariantUsage, CreationBad)
{
    ASSERT_THROW((CreateVar<float, int>(int{})), std::bad_variant_access);
    ASSERT_THROW((CreateVar<size_t, short>(short{})), std::bad_variant_access);
    ASSERT_THROW((CreateVar<char, bool>(bool{})), std::bad_variant_access);
}

// Проверка установки значений
TEST(VariantUsage, SetOkValues)
{
    json::variant<int, bool> var;

    ASSERT_NO_THROW(var = int{});
    ASSERT_NO_THROW(var = bool{});
}

// Проверка установки недоступных значений
TEST(VariantUsage, SetBadValues)
{
    json::variant<int, bool> var;

    ASSERT_THROW(var = float{}, std::bad_variant_access);
    ASSERT_THROW(var = char{}, std::bad_variant_access);
}

// Проверка допустимых типов
TEST(VariantUsage, CheckValidType)
{
    json::variant<int, bool, size_t> var;

    ASSERT_TRUE(var.is_valid_type<int>());
    ASSERT_TRUE(var.is_valid_type<bool>());
    ASSERT_TRUE(var.is_valid_type<size_t>());
}

// Проверка допустимых типов
TEST(VariantUsage, CheckInvalidType)
{
    json::variant<int, bool, size_t> var;

    ASSERT_FALSE(var.is_valid_type<float>());
    ASSERT_FALSE(var.is_valid_type<double>());
    ASSERT_FALSE(var.is_valid_type<char>());
}

// Проверка типа
TEST(VariantUsage, CheckType)
{
    json::variant<int, bool> var;

    ASSERT_NO_THROW(var = int{});
    ASSERT_TRUE(var.is_type<int>());
    ASSERT_FALSE(var.is_type<bool>());

    ASSERT_NO_THROW(var = bool{});
    ASSERT_TRUE(var.is_type<bool>());
    ASSERT_FALSE(var.is_type<int>());
}

// Проверка типа после очистки
TEST(VariantUsage, CheckTypeAfterClear)
{
    json::variant<int, bool> var;

    ASSERT_NO_THROW(var = int{});
    ASSERT_TRUE(var.is_type<int>());

    ASSERT_NO_THROW(var.clear());

    ASSERT_FALSE(var.is_type<int>());
    ASSERT_FALSE(var.is_type<bool>());
}

// Сравнение булевых значений
TEST(VariantUsage, BoolComparison)
{
    json::variant<bool> var;

    var = false;
    ASSERT_TRUE(var == false);
    ASSERT_TRUE(var != true);
    var = true;
    ASSERT_TRUE(var == true);
    ASSERT_TRUE(var != false);
}

// Сравнение целочисленных значений
TEST(VariantUsage, IntComparison)
{
    json::variant<int> var;

    for(int i = -1000; i < 1000; ++i)
    {
        var = i;

        ASSERT_TRUE(var == i);
    }
}

// Сравнение строковых значений
TEST(VariantUsage, StringComparison)
{
    json::variant<std::string> var;
    std::string check;

    for(char c = -128; c < 127; ++c)
    {
        check += c;
        var = check;

        ASSERT_TRUE(var == check);
    }
}
