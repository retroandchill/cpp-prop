#include <iostream>

#include "Property/Property.h"

struct ExampleClass {
    BASIC_PROPERTY(int, property, public, public);
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    ExampleClass example = { 3 };
    std::cout << example.property << std::endl;
    example.property = 10;
    std::cout << example.property << std::endl;
    example.property += 2;
    example.property++;
    std::cout << example.property << std::endl;

    return 0;
}
