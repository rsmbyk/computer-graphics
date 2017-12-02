#include "Cube.hpp"

Cube::Cube ()
: Cube (0, -2, 0, 4) {}

Cube::Cube (float x, float y, float z, float size)
: Box (x-(size/2), x+(size/2), y, y+size, z-(size/2), z+(size/2)) {}
