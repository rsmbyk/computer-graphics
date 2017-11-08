#include "Object.hpp"

Object::Object (GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2, GLfloat x, GLfloat y, GLfloat z) {
    center[X] = x1 + ((x2-x1) * x);
    center[Y] = y1 + ((y2-y1) * y);
    center[Z] = z1 + ((z2-z1) * z);
    margin[X][0] = x1;
    margin[X][1] = x2;
    margin[Y][0] = y1;
    margin[Y][1] = y2;
    margin[Z][0] = z1;
    margin[Z][1] = z2;
}
