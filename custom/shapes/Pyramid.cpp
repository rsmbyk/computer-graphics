#include "Pyramid.hpp"

Pyramid::Pyramid ()
: Pyramid (0, 0, 0, 4, 2, 3) {}

Pyramid::Pyramid (float x, float y, float z, int n, float size, float height)
: Prism (x, y, z, n, size, 0.0, height) {}
