#pragma once

#include <typeindex>
#include <type_traits>
#include <stdexcept>
#include <cstddef>

namespace lazyjson
{

/// @brief Хранилище произвольных типов
/// @tparam ...Ts Шаблонные типы
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

    /// @brief Конструктор копирования
    /// @tparam T Тип значения
    /// @param other Другой объект того же класса
    explicit variant(const variant& other)
    {
        ((copy_value<Ts>(other.m_type, other.m_data) || ...));
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

        return *reinterpret_cast<T*>(m_data);
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

        if(!empty())
        {
            reinterpret_cast<const T*>(m_data)->~T();
        }

        m_data = new T{value};
        m_type = typeid(T);

        return *this;
    }

    /// @brief Очистка содержимого
    void clear()
    {
        if(!empty())
        {
            // Перебираем все шаблонные типы и вызываем их деструкторы
            ((destroy_value<Ts>(m_type) || ...));
        }
    }

    /// @brief Значение отсутствует
    /// @return True, если нет значения
    bool empty() const
    {
        return m_type == typeid(void);
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
    /// @brief Шаблонная функция, удаляющая объект, если он правильного типа
    /// @tparam T сравнимый тип
    /// @param idx индекс типа
    /// @param ptr указатель на данные
    /// @return True, если был вызван деструктор
    template<typename T>
    bool destroy_value(const std::type_index& idx)
    {
        if(idx != typeid(T))
        {
            return false;
        }

        const T* ptr = reinterpret_cast<const T*>(m_data);
        delete ptr;

        m_data = nullptr;
        m_type = typeid(void);

        return true;
    }

    /// @brief Шаблонная функция, копирования объекта, если он правильного типа
    /// @tparam T сравнимый тип
    /// @param idx индекс типа
    /// @param ptr указатель на данные
    /// @return True, если был вызван деструктор
    template<typename T>
    bool copy_value(const std::type_index& idx, const void* other_data)
    {
        if(idx != typeid(T) || !other_data)
        {
            return false;
        }

        clear();

        T** ptr = &reinterpret_cast<T*>(m_data);
        const T* other_ptr = reinterpret_cast<const T*>(other_data);
        *ptr = new T{*other_ptr};

        m_type = typeid(T);

        return true;
    }

private:
    /// @brief Размер хранилища
    static constexpr size_t m_max_size = sizeof(std::aligned_union_t<0, Ts...>);

    /// @brief Размер выравнивания
    static constexpr size_t m_alignment = alignof(std::aligned_union_t<0, Ts...>);

    /// @brief Хранимый тип
    std::type_index m_type{typeid(void)};

    /// @brief Хранилище
    void* m_data = nullptr;
};

} // namespace lazyjson
