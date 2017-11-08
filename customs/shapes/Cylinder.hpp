#ifndef COMPUTER_GRAPHICS_CYLINDER_HPP
#define COMPUTER_GRAPHICS_CYLINDER_HPP

#include "Prism.hpp"

// Cylinder is a prism with a lot of slice (n)
class Cylinder : public Prism {
public:
    explicit Cylinder (bool shuffleColor = false);
    Cylinder (GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height, bool shuffleColor = false);
};

#endif // COMPUTER_GRAPHICS_CYLINDER_HPP
