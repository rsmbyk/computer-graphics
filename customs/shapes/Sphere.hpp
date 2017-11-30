#ifndef COMPUTER_GRAPHICS_BALL_HPP
#define COMPUTER_GRAPHICS_BALL_HPP

#include <customs/base/Object.hpp>

class Sphere : public Object {
public:
    Sphere ();
    Sphere (GLfloat x, GLfloat y, GLfloat z, GLfloat r);
    void render () override;
    void clean () override;
    void transform (mat4 T, int type) override;
    void measure () override;

private:
    GLfloat *buffer;
    GLfloat *colors;
    GLuint vaoID, vboID, cboID;
    GLint N = 360;
    GLint BUFFER_LENGTH, BUFFER_SIZE;
};

#endif // COMPUTER_GRAPHICS_BALL_HPP
