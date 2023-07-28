#pragma once

#include <typeindex>
#include <type_traits>
#include <stdexcept>
#include <cstddef>

namespace lazyjson
{

/// @brief Хранилище произвольных типов
/// @tparam ...Ts
template<typename... Ts>
class variant
{
public:
    /// @brief Конструктор по умолчанию
    variant()
    {
    }

    /// @brief Конструктор с присваиванием значения
    /// @tparam T Тип значения
    /// @param value Значение
    template<typename T>
    explicit variant(const T& value)
    {
        operator=(value);
    }

    /// @brief Деструктор
    ~variant()
    {
        clear();
    }

    /// @brief Является ли хранимое значение искомого типа
    /// @tparam T искомый тип
    /// @return True, если является
    template<typename T>
    bool is_type() const
    {
        return m_type == typeid(T);
    }

    /// @brief Получить значение требуемого типа
    /// @tparam T тип значения
    /// @return Значение
    template<typename T>
    T get() const
    {
        if(!is_type<T>())
        {
            throw std::bad_variant_access();
        }

        return *reinterpret_cast<const T*>(m_data);
    }

    /// @brief Получить значение требуемого типа
    /// @tparam T тип значения
    /// @return Значение
    template<typename T>
    T& get()
    {
        if(!is_type<T>())
        {
            throw std::bad_variant_access();
        }

        return *reinterpret_cast<const T*>(m_data);
    }

    /// @brief Оператор сравнения
    /// @tparam T тип
    /// @param value значение
    /// @return True, если значения равны
    template<typename T>
    bool operator==(const T& value)
    {
        if(m_type != typeid(T))
        {
            throw std::bad_variant_access();
        }

        const auto& data = *reinterpret_cast<const T*>(m_data);
        return data == value;
    }

    /// @brief Оператор сравнения
    /// @tparam T тип
    /// @param value значение
    /// @return True, если значения не равны
    template<typename T>
    bool operator!=(const T& value)
    {
        return !operator==(value);
    }

    /// @brief Оператор присваивания для значения требуемого типа
    /// @tparam T тип значения
    /// @return Ссылка на экземпляр
    template<typename T>
    variant& operator=(const T& value)
    {
        if(!is_valid_type<T>())
        {
            throw std::bad_variant_access();
        }

        if(m_type != typeid(void))
        {
            reinterpret_cast<const T*>(m_data)->~T();
        }

        new(m_data) T(value);
        m_type = typeid(T);

        return *this;
    }

    /// @brief Очистка содержимого
    void clear()
    {
        if(m_type != typeid(void))
        {
            void* data_ptr = static_cast<void*>(m_data);
            std::destroy_at(static_cast<typename std::aligned_union<0, Ts...>::type*>(data_ptr));
            std::memset(data_ptr, 0, m_max_size);
            m_type = typeid(void);
        }
    }

    /// @brief Проверка допустим ли тип
    /// @tparam T тип
    /// @return True, если да
    template<typename T>
    bool is_valid_type() const
    {
        return ((std::is_same_v<T, Ts> || ...));
    }

private:
    /// @brief Размер хранилища
    static constexpr size_t m_max_size = sizeof(std::aligned_union_t<0, Ts...>);

    /// @brief Размер выравнивания
    static constexpr size_t m_alignment = alignof(std::aligned_union_t<0, Ts...>);

    /// @brief Хранимый тип
    std::type_index m_type = typeid(void);

    /// @brief Хранилище
    std::byte m_data[m_max_size];
};

} // namespace lazyjson
