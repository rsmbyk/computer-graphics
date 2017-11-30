#include "Cone.hpp"

Cone::Cone ()
: Cone (0, 0, 0, 2, 4, true) {}

Cone::Cone (GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height, bool shuffleColor)
: Pyramid (x, y, z, 360, r, height, shuffleColor) {}
