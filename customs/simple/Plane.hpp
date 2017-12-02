#ifndef COMPUTER_GRAPHICS_PLANE_HPP
#define COMPUTER_GRAPHICS_PLANE_HPP

#include "customs/shapes/Box.hpp"

class Plane : public Box {
public:
    Plane ();
    Plane (float x, float y, float z, float size);
};

#endif // COMPUTER_GRAPHICS_PLANE_HPP
