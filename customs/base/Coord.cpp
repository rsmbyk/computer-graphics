#include "Coord.hpp"

Coord::Coord () : x (0), y (0), z (0) {}

Coord::Coord (GLfloat x, GLfloat y, GLfloat z) : x (x), y (y), z (z) {}

void Coord::set (GLfloat x, GLfloat y, GLfloat z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
