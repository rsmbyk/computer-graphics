#ifndef COMPUTER_GRAPHICS_CUBE_HPP
#define COMPUTER_GRAPHICS_CUBE_HPP

#include <GL/gl.h>
#include "Box.hpp"

class Cube : public Box {
public:
    Cube ();
    Cube (float x, float y, float z, float size);
};

#endif // COMPUTER_GRAPHICS_CUBE_HPP
