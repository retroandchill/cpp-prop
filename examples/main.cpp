#include <iostream>

#include "Property/Property.h"

struct ExampleClass {
    PROPERTY_META(ExampleClass);

    PROPERTY(int, property, public, public);
    PROPERTY(int, dynamic, public, public);
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

    return 0;
}
