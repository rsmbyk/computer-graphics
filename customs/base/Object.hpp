#ifndef COMPUTER_GRAPHICS_OBJECT_HPP
#define COMPUTER_GRAPHICS_OBJECT_HPP

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
 *
 * + Do not forget to call init at the end of constructor
 *   to make sure it is measured properly.
 */

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#define printVec(x) for (int ii = 0; ii < 3; ii++) printf ("%.12f ", (x)[ii]); printf ("\n");

using namespace glm;

// TODO: try to use VBO indexing for better performance and experience.

class Object {
public:
    virtual void onInit ();
    virtual void onRender ();
    virtual void onClean ();
    virtual void onMeasureMargin ();
    virtual void onTransform (mat4 T);
    void init ();
    void render ();
    void updateBuffer ();
    void clean ();
    void measure ();
    void measureCenter ();
    void measureMargin ();
    void transform (mat4 T);
    void translate (vec3 v);
    void translateTo (vec3 to, float speed);
    void orbit (vec3 angle, vec3 orbitCenter);
    void rotateAt (vec3 angle, vec3 centerOfRotation);
    void rotate (vec3 angle);
    void scale (vec3 ratio, vec3 scalingCenter);
    void scaleToAt (vec3 ratio, vec3 scalingCenter);
    void scaleAt (vec3 ratio, vec3 scalingCenter);
    void scaleTo (vec3 ratio);
    void scaleBy (vec3 ratio);
    vec3 getCoordinate (vec3 coordinates);
    
    // axis constants
    // static const int X=0, Y=1, Z=2;
    #define X 0
    #define Y 1
    #define Z 2
    
    // transform constants
    // static const int TRANSLATE=0, ROTATE=1, SCALE=2;
    // #define TRANSLATE 0
    // #define ROTATE 1
    // #define SCALE 2
    
    // colors array need to be defined as class attribute
    // so that it can be changed after initialization.
    float *buffer;
    float *colors;
    unsigned int vaoID, vboID, cboID;
    int BUFFER_LENGTH, BUFFER_SIZE, TRIANGLE_COUNT;
    
    // translateTo related field
    vec3 translateToTarget, translateToDiff;
    double translateToLastTime, translateToTotalDist, translateToDist;
    bool translateToIdle;
    
    double lastRenderTime;
    mat4 transform_matrix;
    vec3 rotationAngle, translationDistance, scaleRatio;
    vec3 center, initialCenter;
    vec3 margin[2], initialMargin[2];
    float x, y, z;
    float x1, x2, y1, y2, z1, z2;
};

#endif // COMPUTER_GRAPHICS_OBJECT_HPP
