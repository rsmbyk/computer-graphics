#ifndef COMPUTER_GRAPHICS_CONE_HPP
#define COMPUTER_GRAPHICS_CONE_HPP

#include "Pyramid.hpp"

// Cone is a pyramid with a lot of n
class Cone : public Pyramid {
public:
    Cone ();
    Cone (float x, float y, float z, float r, float height);
};

#endif // COMPUTER_GRAPHICS_CONE_HPP
