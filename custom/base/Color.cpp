#include <cstdlib>
#include "Color.hpp"

#define randomFloat (float) rand () / RAND_MAX // NOLINT
#define randomVec3 {randomFloat, randomFloat, randomFloat}

Color::Color () : Color (randomVec3) {}

Color::Color (float r, float g, float b) {
    set (r, g, b);
}

void Color::set (float r, float g, float b) {
    color = vec3 (r, g, b);
    if (color.r > 1.0f || color.g > 1.0f || color.b > 1.0f)
        color /= 255.0f;
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
}

float Color::operator[] (int i) {
    return color[i];
}
