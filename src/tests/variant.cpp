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

// Присваивание булевых значений
TEST(VariantUsage, BoolSetValue)
{
    json::variant<bool> var;

    bool test;
    var = true;
    ASSERT_NO_THROW(test = var.get<bool>());
    ASSERT_TRUE(var == test);

    ASSERT_THROW(int test = var.get<int>(), std::bad_variant_access);
}

// Присваивание целочисленных значений
TEST(VariantUsage, IntSetValue)
{
    json::variant<int> var;

    for(int i = -1000; i < 1000; ++i)
    {
        var = i;

        ASSERT_TRUE(var == i);

        int test;
        ASSERT_NO_THROW(test = var.get<int>());
        ASSERT_TRUE(var == test);

        ASSERT_THROW(std::string test = var.get<std::string>(), std::bad_variant_access);
    }
}

// Присваивание строковых значений
TEST(VariantUsage, StringSetValue)
{
    json::variant<std::string> var;
    std::string check;

    for(char c = -128; c < 127; ++c)
    {
        check += c;
        var = check;

        ASSERT_TRUE(var == check);

        std::string test = var.get<std::string>();

        ASSERT_TRUE(var == test);
        ASSERT_TRUE(check == test);

        ASSERT_THROW(int test = var.get<int>(), std::bad_variant_access);
    }
}

class Deleteable
{
public:
    Deleteable(bool& flag)
        : m_flag{flag}
    {
    }

    Deleteable(Deleteable&& other)
        : m_flag{other.m_flag}
    {
        static bool staticFlag;
        other.m_flag = staticFlag;
    }

    Deleteable(const Deleteable& other)
        : m_flag{other.m_flag}
    {
    }

    ~Deleteable()
    {
        m_flag = !m_flag;
    }

private:
    bool& m_flag;
};

// Уничтожение экземпляра класса
TEST(VariantUsage, DestroyClassInstance)
{
    json::variant<Deleteable> var;

    bool isDeleted = false;
    var = Deleteable{isDeleted};

    ASSERT_FALSE(var.empty());

    var.clear();
    ASSERT_TRUE(var.empty());
    ASSERT_TRUE(isDeleted);
}
