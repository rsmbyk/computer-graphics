#ifndef COMPUTER_GRAPHICS_VECTOR_OPERATIONS_HPP
#define COMPUTER_GRAPHICS_VECTOR_OPERATIONS_HPP

#include <glm/vec3.hpp>
#include <utility>

using namespace glm;

namespace grafkom {
    double length (vec3 v);
    vec3 between (vec3 a, vec3 b, float t);
    vec3 angleVector (vec3 a, vec3 b);
}

#endif // COMPUTER_GRAPHICS_VECTOR_OPERATIONS_HPP
