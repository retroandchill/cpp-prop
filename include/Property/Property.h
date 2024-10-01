//
// Created by fcors on 10/1/2024.
//
#pragma once
#include <cstddef>


#define PROPERTY_META(T) using Self = T

#define DEFAULT_GET(T, name) \
    constexpr T& _get_##name() { \
        return name.value; \
    }

#define DEFAULT_SET(T, name) \
    template <typename A> \
        requires std::assignable_from<T&, A> \
    constexpr void _set_##name(A&& val) { \
        name.value = std::forward<A>(val); \
    }

#define PROPERTY_PRIVATE(T, name, getter_access, const_getter_access, getter, setter_access, setter) \
        public: \
        class Property_##name { \
        private: \
            constexpr Self& getEnclosing() const { \
                return *reinterpret_cast<Self *>((char *) this - offsetof(Self, ##name)); \
            } \
            public: \
            template <typename... A> \
                requires std::constructible_from<T, A...> \
            constexpr Property_##name(A&&... args) : value(std::forward<A>(args)...) {} \
            getter_access: \
            constexpr operator T&() { \
                return getEnclosing()._get_##name(); \
            } \
            const_getter_access: \
            constexpr operator const T&() const { \
                return getEnclosing()._get_##name(); \
            } \
            public: \
            template <typename A> \
                requires std::assignable_from<T&, A> \
            constexpr Property_##name& operator=(A&& val) { \
                getEnclosing()._set_##name(std::forward<A>(val)); \
                return *this; \
            } \
            private: \
            friend Self; \
            int value; \
        }; \
        Property_##name name; \
        getter(T, name) \
        setter(T, name)

#define PROPERTY(T, name, getter_access, setter_access) \
    PROPERTY_PRIVATE(T, name, getter_access, getter_access, DEFAULT_GET, setter_access, DEFAULT_SET)