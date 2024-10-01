//
// Created by fcors on 10/1/2024.
//
#pragma once

#include <type_traits>
#include <utility>

namespace Prop {

template <typename T>
class BasicProperty {

  public:
    BasicProperty() requires std::is_default_constructible_v<T> = default;

    template <typename... A>
      requires std::constructible_from<T, A...>
  BasicProperty(A&&... args) : value(std::forward<A>(args)...) {}

  operator T&() {
      return value;
    }

    operator const T&() const {
      return value;
    }

    template <typename A>
      requires std::assignable_from<T, A>
    BasicProperty& operator=(A&& arg) {
      value = std::forward<A>(arg);
      return *this;
    }

  private:
    T value;
};

}
