#ifndef COMPUTER_GRAPHICS_PYRAMID_HPP
#define COMPUTER_GRAPHICS_PYRAMID_HPP

#include "Prism.hpp"

// Pyramid is a prism with cover size of 0
class Pyramid : public Prism {
public:
    Pyramid ();
    Pyramid (float x, float y, float z, int n, float size, float height);
};

#endif // COMPUTER_GRAPHICS_PYRAMID_HPP
