#ifndef COMPUTER_GRAPHICS_COLOR_HPP
#define COMPUTER_GRAPHICS_COLOR_HPP

#include <glm/vec3.hpp>

using namespace glm;

class Color {
public:
    float r, g, b;
    vec3 color;
    
    Color ();
    Color (float r, float g, float b);
    void set (float r, float g, float b);
    float operator[] (int i);
};

#endif // COMPUTER_GRAPHICS_COLOR_HPP
