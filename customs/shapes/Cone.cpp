#include "Cone.hpp"

Cone::Cone (bool shuffleColor)
: Cone (0, 0, 0, 2, 4, shuffleColor) {}

Cone::Cone (GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height, bool shuffleColor)
: Pyramid (x, y, z, 360, r, height, shuffleColor) {}
