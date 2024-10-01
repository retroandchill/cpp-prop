//
// Created by fcors on 10/1/2024.
//
#pragma once
#include <cstddef>


#define PROPERTY_META(T) using Self = T;

#define PUBLIC_GET()

#define BASIC_PROPERTY_PRIVATE(T, name, getter_access, const_getter_access, setter_access) \
    public: \
    class Property_##name { \
    public: \
        template<typename... A> \
            requires std::constructible_from<T, A...> \
        constexpr Property_##name(A &&... args) : value(std::forward<A>(args)...) {} \
        getter_access: \
        constexpr operator T &() { \
            return value; \
        } \
        const_getter_access: \
        constexpr operator const T &() const { \
            return value;\
        } \
        setter_access: \
        template<typename A> \
            requires std::assignable_from<T, A> \
        constexpr Property_##name &operator=(A &&arg) { \
            value = std::forward<A>(arg); \
            return *this; \
        } \
    private: \
        T value; \
    }; \
    Property_##name name

#define BASIC_PROPERTY(T, name, getter_access, setter_access) BASIC_PROPERTY_PRIVATE(T, name, getter_access, getter_access, setter_access)

