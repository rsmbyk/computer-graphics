#ifndef COMPUTER_GRAPHICS_COORD_HPP
#define COMPUTER_GRAPHICS_COORD_HPP

#include <GL/gl.h>

class Coord {
public:
    GLfloat x, y, z;
    
    Coord ();
    Coord (GLfloat x, GLfloat y, GLfloat z);
    void set (GLfloat x, GLfloat y, GLfloat z);
};

#endif // COMPUTER_GRAPHICS_COORD_HPP
