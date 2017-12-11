#ifndef COMPUTER_GRAPHICS_CYLINDER_HPP
#define COMPUTER_GRAPHICS_CYLINDER_HPP

#include "Prism.hpp"

// Cylinder is a prism with a lot of slice (n)
class Cylinder : public Prism {
public:
    Cylinder ();
    Cylinder (float x, float y, float z, float r, float height);
};

#endif // COMPUTER_GRAPHICS_CYLINDER_HPP
