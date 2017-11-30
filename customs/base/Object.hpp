#ifndef COMPUTER_GRAPHICS_OBJECT_HPP
#define COMPUTER_GRAPHICS_OBJECT_HPP

#include <GL/gl.h>
#include <glm/detail/type_mat4x4.hpp>

using namespace glm;

/**
 * + ao = array object
 *   bo = buffer object
 *   vao = vector ao
 *   vbo = vector bo
 *   cbo = vector bo
 *
 * + All objects has empty constructor which will create
 *   the object in the center of the map (x=0, y=0, z=0)
 *   (in front of initial camera position).
 */

// TODO: try to use VBO indexing for better performance and experience.

class Object {
public:
    Object (GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2);
    
    virtual void render () = 0;
    virtual void clean () = 0;
    virtual void transform (mat4 T, int type) = 0;
    virtual void measure () = 0;
    void _transform (mat4 T, int type);
    void _measure ();
    void _measureCenter ();
    void _measureMargin ();
    void translate (GLfloat x, GLfloat y, GLfloat z);
    void rotate (GLfloat x, GLfloat y, GLfloat z);
    void orbit (GLfloat x, GLfloat y, GLfloat z, GLfloat xCenter, GLfloat yCenter, GLfloat zCenter);
    void scale (GLfloat x, GLfloat y, GLfloat z);
    void scaleTo (GLfloat x, GLfloat y, GLfloat z);
    
    // axis constants
    // static const int X=0, Y=1, Z=2;
    #define X 0
    #define Y 1
    #define Z 2
    
    // transform constants
    // static const int TRANSLATE=0, ROTATE=1, SCALE=2;
    #define TRANSLATE 0
    #define ROTATE 1
    #define SCALE 2
    
    GLfloat center[3], margin[3][2];
    GLfloat x, y, z;
    GLfloat x1, x2, y1, y2, z1, z2;
};

#endif // COMPUTER_GRAPHICS_OBJECT_HPP
