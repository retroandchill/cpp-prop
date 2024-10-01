project(cpp_prop)

add_library(cpp_prop INTERFACE
        Property/Property.h)

target_include_directories(cpp_prop INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR})