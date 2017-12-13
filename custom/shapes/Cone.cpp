#include "Cone.hpp"

Cone::Cone ()
: Cone (0, 0, 0, 2, 4) {}

Cone::Cone (float x, float y, float z, float r, float height)
: Pyramid (x, y, z, 45, r, height) {}
