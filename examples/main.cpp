#include <iostream>

#include "Property/Property.h"

struct ExampleClass {
    PROPERTY_META(ExampleClass);

    PROPERTY(int, property, public, DEFAULT_GET, public, DEFAULT_SET);
    PROPERTY(int, dynamic, public, DEFAULT_GET, public, DEFAULT_SET);
    PROPERTY(std::string, declared, public, DECLARED_GET, public, DECLARED_SET);
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    ExampleClass example;
    std::cout << example.property << std::endl;
    example.property = 10;
    std::cout << example.property << std::endl;
    example.property += 2;
    example.property++;
    std::cout << example.property << std::endl;

    std::cout << example.dynamic << std::endl;
    example.dynamic = 10;
    std::cout << example.dynamic << std::endl;
    example.dynamic += 2;
    example.dynamic++;
    std::cout << example.dynamic << std::endl;

    example.declared = "Hello, World!";
    std::cout << *example.declared << std::endl;

    return 0;
}

DEFINE_GET(ExampleClass, std::string, declared) {
    return declared.value;
}

DEFINE_LVALUE_SET(ExampleClass, std::string, declared) {
    declared.value = value;
}

DEFINE_RVALUE_SET(ExampleClass, std::string, declared) {
    declared.value = std::move(value);
}