#include "Cube.hpp"

Cube::Cube (bool shuffleColor) : Cube (0, 0, 0, 2, shuffleColor) {}

Cube::Cube (GLfloat x, GLfloat y, GLfloat z, GLfloat size, bool shuffleColor)
: Box (x-(size/2), x+(size/2), y, y+size, z-(size/2), z+(size/2), shuffleColor) {}
