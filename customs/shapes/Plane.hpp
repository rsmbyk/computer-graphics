#ifndef COMPUTER_GRAPHICS_PLANE_HPP
#define COMPUTER_GRAPHICS_PLANE_HPP

#include "Box.hpp"

class Plane : public Box {
public:
    Plane ();
    Plane (GLfloat x, GLfloat y, GLfloat z, GLfloat size);
    Plane (GLfloat x, GLfloat y, GLfloat z, GLfloat size, Color color);
};

#endif // COMPUTER_GRAPHICS_PLANE_HPP
