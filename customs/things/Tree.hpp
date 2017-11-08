#ifndef COMPUTER_GRAPHICS_TREE_HPP
#define COMPUTER_GRAPHICS_TREE_HPP

#include <customs/shapes/Cone.hpp>
#include <customs/shapes/Cylinder.hpp>

class Tree : public Object {
public:
    Tree (GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height);
    Tree (GLfloat x, GLfloat y, GLfloat z, int size);
    
    void render () override;
    void clean () override;
    void move (int coord, GLfloat amount) override;
    void rotate (GLfloat x, GLfloat y, GLfloat z) override;
    void scale (GLfloat x, GLfloat y, GLfloat z) override;

private:
    Cylinder trunk;
    Cone leaves;
};

#endif // COMPUTER_GRAPHICS_TREE_HPP
