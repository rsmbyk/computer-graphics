#include "Pyramid.hpp"

Pyramid::Pyramid ()
: Pyramid (0, 0, 0, 4, 2, 3, true) {}

Pyramid::Pyramid (GLfloat x, GLfloat y, GLfloat z, int n, GLfloat size, GLfloat height, bool shuffleColor)
: Prism (x, y, z, n, size, 0.0, height, shuffleColor) {}
