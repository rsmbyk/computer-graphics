#include "Cylinder.hpp"

Cylinder::Cylinder (bool shuffleColor)
: Cylinder (0, 0, 0, 2, 4, shuffleColor) {}

Cylinder::Cylinder (GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height, bool shuffleColor)
: Prism (x, y, z, 360, r, height, shuffleColor) {}
