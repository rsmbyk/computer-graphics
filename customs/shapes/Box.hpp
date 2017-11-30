#ifndef COMPUTER_GRAPHICS_BOX_HPP
#define COMPUTER_GRAPHICS_BOX_HPP

#include <customs/base/Object.hpp>
#include <customs/base/Color.hpp>
#include <glm/glm.hpp>

class Box : public Object {
public:
    Box ();
    Box (GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2, bool shuffleColor = false);
    
    void render () override;
    void clean () override;
    void transform (mat4 T, int type) override;
    void measure () override;
    
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

    // colors array need to be defined as class attribute
    // so that it can be changed after initialization.
    GLfloat *buffer;
    GLfloat *colors;
    GLuint vaoID, vboID, cboID;
    GLint BUFFER_LENGTH = 108;
    GLint BUFFER_SIZE = 108 * sizeof (GLfloat*);
};

#endif // COMPUTER_GRAPHICS_BOX_HPP
