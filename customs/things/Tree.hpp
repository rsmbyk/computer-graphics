#ifndef COMPUTER_GRAPHICS_TREE_HPP
#define COMPUTER_GRAPHICS_TREE_HPP

#include <customs/shapes/Cone.hpp>
#include <customs/shapes/Cylinder.hpp>
#include "Thing.hpp"

class Tree : public Thing {
public:
    Tree (GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height);
    Tree (GLfloat x, GLfloat y, GLfloat z, int size);

private:
    Cylinder trunk;
    Cone leaves;
};

#endif // COMPUTER_GRAPHICS_TREE_HPP
