#include "Plane.hpp"

Plane::Plane ()
: Plane (0, -1, 0, 20) {}

Plane::Plane (GLfloat x, GLfloat y, GLfloat z, GLfloat size)
: Plane (x, y, z, size, Color (109, 88, 74, true)) {}

Plane::Plane (GLfloat x, GLfloat y, GLfloat z, GLfloat size, Color color)
: Box (x-(size/2), x+(size/2), y-0.1f, y, z-(size/2), z+(size/2)) {
    setFaceColor (TOP, color);
}
