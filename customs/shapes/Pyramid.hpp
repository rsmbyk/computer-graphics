#ifndef COMPUTER_GRAPHICS_PYRAMID_HPP
#define COMPUTER_GRAPHICS_PYRAMID_HPP

#include "Prism.hpp"

// Pyramid is a prism with cover size of 0
class Pyramid : public Prism {
public:
    explicit Pyramid (bool shuffleColor = false);
    Pyramid (GLfloat x, GLfloat y, GLfloat z, int n, GLfloat size, GLfloat height, bool shuffleColor = false);
};

#endif // COMPUTER_GRAPHICS_PYRAMID_HPP
