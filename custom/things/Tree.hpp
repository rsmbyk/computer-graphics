#ifndef COMPUTER_GRAPHICS_TREE_HPP
#define COMPUTER_GRAPHICS_TREE_HPP

#include <custom/shapes/Cylinder.hpp>
#include <custom/shapes/Cone.hpp>
#include "Thing.hpp"

class Tree : public Thing {
public:
    Tree (float x, float y, float z, float r, float height);
    Tree (float x, float y, float z, int size);

private:
    Cylinder *trunk;
    Cone *leaves;
};

#endif // COMPUTER_GRAPHICS_TREE_HPP
