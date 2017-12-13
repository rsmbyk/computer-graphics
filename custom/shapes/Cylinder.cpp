#include "Cylinder.hpp"

Cylinder::Cylinder ()
: Cylinder (0, 0, 0, 2, 4) {}

Cylinder::Cylinder (float x, float y, float z, float r, float height)
: Prism (x, y, z, 45, r, height) {}
