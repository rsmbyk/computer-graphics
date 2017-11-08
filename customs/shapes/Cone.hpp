#ifndef COMPUTER_GRAPHICS_CONE_HPP
#define COMPUTER_GRAPHICS_CONE_HPP

#include "Pyramid.hpp"

// Cone is a pyramid with a lot of n
class Cone : public Pyramid {
public:
    explicit Cone (bool shuffleColor = false);
    Cone (GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height, bool shuffleColor = false);
};

#endif // COMPUTER_GRAPHICS_CONE_HPP
