#include "Plane.hpp"

Plane::Plane ()
: Plane (0, -1, 0, 20) {}

Plane::Plane (float x, float y, float z, float size)
: Box (x-(size/2), x+(size/2), y-0.1f, y, z-(size/2), z+(size/2)) {
    setColor ({81, 66, 55});
    setFaceColor (TOP, {109, 88, 74});
    setFaceColor (BOTTOM, {60, 49, 41});
}
