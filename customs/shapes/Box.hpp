#ifndef COMPUTER_GRAPHICS_BOX_HPP
#define COMPUTER_GRAPHICS_BOX_HPP

#include <customs/base/Object.hpp>
#include <customs/base/Coord.hpp>
#include <customs/base/Color.hpp>
#include <glm/glm.hpp>

class Box : public Object {
public:
    explicit Box (bool shuffleColor = false);
    Box (GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2, bool shuffleColor = false);
    
    void render () override;
    void clean () override;
    void move (int coord, GLfloat amount) override;
    void rotate (GLfloat x, GLfloat y, GLfloat z) override;
    void scale (GLfloat x, GLfloat y, GLfloat z) override;
    
    Box *setFaceColor (int face, Color color);
    
    // Constants to represents each faces of the box.
    // The order of enum must follow vertex array
    // draw order.
    static const int LEFT=0, TOP=1, FRONT=2, RIGHT=3, BOTTOM=4, REAR=5;

protected:
    // colors array need to be defined as class attribute
    // so that it can be changed after initialization.
    GLfloat *buffer;
    GLfloat *colors;
    GLuint vaoID, vboID, cboID;
    const int BUFFER_LENGTH = 108;
};

#endif // COMPUTER_GRAPHICS_BOX_HPP
