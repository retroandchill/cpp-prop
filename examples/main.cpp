#include <iostream>

#include "Property/BasicProperty.h"

struct ExampleClass {
    Prop::BasicProperty<int> property;
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
