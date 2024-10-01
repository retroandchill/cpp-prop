//
// Created by fcors on 10/1/2024.
//
#pragma once
#include <cstddef>


#define PROPERTY_META(T) using Self = T

#define DEFAULT_GET(T, name) \
    constexpr const T& _get_##name() const { \
        return name.value; \
    }

#define DECLARED_GET(T, name) const T& _get_##name() const;

#define DEFINE_GET(Class, T, name) const T& Class::_get_##name() const

#define DEFAULT_SET(T, name) \
    template <typename A> \
        requires std::assignable_from<T&, A> \
    constexpr void _set_##name(A&& value) { \
        name.value = std::forward<A>(value); \
    }

#define DECLARED_LVALUE_SET(T, name) void _set_##name(const T& value);

#define DECLARED_RVALUE_SET(T, name) void _set_##name(T&& value);

#define DECLARED_SET(T, name) \
    DECLARED_LVALUE_SET(T, name) \
    DECLARED_RVALUE_SET(T, name)

#define DEFINE_LVALUE_SET(Class, T, name) void Class::_set_##name(const T& value)

#define DEFINE_RVALUE_SET(Class, T, name) void Class::_set_##name(T&& value)

#define PROPERTY_PRIVATE(T, name, getter_access, const_getter_access, getter, setter_access, setter) \
        public: \
        class Property_##name { \
        private: \
            constexpr Self& getEnclosing() const { \
                return *reinterpret_cast<Self *>((char *) this - offsetof(Self, name)); \
            } \
            public: \
            template <typename... A> \
                requires std::constructible_from<T, A...> \
            constexpr Property_##name(A&&... args) : value(std::forward<A>(args)...) {} \
            getter_access: \
            constexpr operator T&() { \
                return const_cast<T&>(getEnclosing()._get_##name()); \
            } \
            constexpr T& operator*() { \
                return const_cast<T&>(getEnclosing()._get_##name()); \
            } \
            constexpr T* operator->() { \
                return &const_cast<T&>(getEnclosing()._get_##name()); \
            } \
            const_getter_access: \
            constexpr operator const T&() const { \
                return getEnclosing()._get_##name(); \
            } \
            constexpr const T& operator*() const { \
                return getEnclosing()._get_##name(); \
            } \
            constexpr const T* operator->() const { \
                return &getEnclosing()._get_##name(); \
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
            T value; \
        }; \
        private: \
        getter(T, name) \
        setter(T, name) \
        public: \
        Property_##name name;

#define PROPERTY(T, name, getter_access, getter, setter_access, setter) \
    PROPERTY_PRIVATE(T, name, getter_access, getter_access, getter, setter_access, setter)