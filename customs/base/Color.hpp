#ifndef COMPUTER_GRAPHICS_COLOR_HPP
#define COMPUTER_GRAPHICS_COLOR_HPP

#include <GL/gl.h>

class Color {
public:
    GLfloat r, g, b;
    
    explicit Color (bool shuffleColor = false);
    Color (GLfloat r, GLfloat g, GLfloat b, bool hex);
    void set (GLfloat r, GLfloat g, GLfloat b);
};

#endif // COMPUTER_GRAPHICS_COLOR_HPP
