#ifndef COMPUTER_GRAPHICS_BOX_HPP
#define COMPUTER_GRAPHICS_BOX_HPP

#include <custom/base/Object.hpp>
#include <custom/base/Color.hpp>

class Box : public Object {
public:
    Box ();
    Box (float x1, float x2, float y1, float y2, float z1, float z2);
    
    void setFaceColor (int face, Color color);
    void setColor (Color color);
    
    // Constants to represents each faces of the box.
    // The order of enum must follow vertex array
    // draw order.
    // static const int LEFT=0, TOP=1, FRONT=2, RIGHT=3, BOTTOM=4, REAR=5;
    #define LEFT 0
    #define TOP 1
    #define FRONT 2
    #define RIGHT 3
    #define BOTTOM 4
    #define REAR 5
};

#endif // COMPUTER_GRAPHICS_BOX_HPP
