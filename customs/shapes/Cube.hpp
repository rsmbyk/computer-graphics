#ifndef COMPUTER_GRAPHICS_CUBE_HPP
#define COMPUTER_GRAPHICS_CUBE_HPP

#include <GL/gl.h>
#include "Box.hpp"

class Cube : public Box {
public:
    Cube ();
    Cube (GLfloat x, GLfloat y, GLfloat z, GLfloat size, bool shuffleColor = false);
};

#endif // COMPUTER_GRAPHICS_CUBE_HPP
