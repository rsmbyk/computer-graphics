#ifndef COMPUTER_GRAPHICS_PLANE_HPP
#define COMPUTER_GRAPHICS_PLANE_HPP

#include "custom/shapes/Box.hpp"

class Plane : public Box {
public:
    Plane (float groundLevel, float groundSize);
};

#endif // COMPUTER_GRAPHICS_PLANE_HPP
