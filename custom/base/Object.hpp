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
 */

#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <cfloat>

#define printVec(vv,nn) for (int ii = 0; ii < (nn); ii++) printf ("%.12f ", (vv)[ii]); printf ("\n");
#define printVec3(vv) printVec ((vv), 3)
#define printVec4(vv) printVec ((vv), 4)
#define printMat(mm,nn) for (int iii = 0; iii < (nn); iii++) { printVec4 ((mm)[iii]); }
#define printMat4(mm) printMat ((mm), 4)

using namespace glm;
using namespace std;

// TODO: try to use VBO indexing for better performance and experience.

class Object {
public:
    Object ();
    
    // overridable methods
    virtual void onInit ();
    virtual void onRender ();
    virtual void onClean ();
    virtual void onMeasureMargin ();
    virtual void onTransform (mat4 T);
    
    // base methods
    void init ();
    void render ();
    void updateBuffer ();
    void clean ();
    void measure ();
    void measureCenter ();
    void measureMargin ();
    void transform (mat4 T);
    
    // translation-related methods
    void translate (vec3 amount);
    void translateTo (vec3 to, vec3 shift);
    void translateTo (vec3 to);
    
    // rotation-related methods
    void rotateToAt (quat rotation, vec3 pivot);
    void rotateToAt (vec3 angle, vec3 pivot);
    void rotateTo (quat rotation, vec3 centerOfRotation);
    void rotateTo (quat rotation);
    void rotateTo (vec3 angle, vec3 centerOfRotation);
    void rotateTo (vec3 angle);
    void rotateAt (quat rotation, vec3 pivot);
    void rotateAt (vec3 angle, vec3 pivot);
    void rotate (quat rotation, vec3 centerOfRotation);
    void rotate (quat rotation);
    void rotate (vec3 angle, vec3 centerOfRotation);
    void rotate (vec3 angle);
    void rotateReset ();
    
    // scaling-related methods
    void scaleToAt (vec3 ratio, vec3 pivot);
    void scaleTo (vec3 ratio, vec3 scalingCenter);
    void scaleTo (vec3 ratio);
    void scaleAt (vec3 ratio, vec3 pivot);
    void scale (vec3 ratio, vec3 scalingCenter);
    void scale (vec3 ratio);
    
    // pivot-related methods
    vec3 getInitialPivot (vec3 pivot);
    vec3 getPivot (vec3 pivot);
    
    // path-related methods
    void setWalkPath (vector<vec3> path, vec3 pivot, float speed);
    void setWalkPath (vector<vec3> path, float speed);
    virtual void onSetWalkPath ();
    vec3 getWalkPoint (int i);
    void walk ();
    void setWalkProgress (int progress);
    virtual void onWalk (double amount);
    
    // TODO: lower unnecessary public fields to private or protected.
    
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
    
    // walk related field
    vector<vec3> walkPath;
    vec3 walkPivot;
    double walkLastTime;
    float walkSpeed;
    int walkProgress, walkNext;
    
    double lastRenderTime;
    mat4 transform_matrix;
    quat rotationQuat;
    vec3 translationDistance, scaleRatio;
    vec3 center, initialCenter;
    vec3 margin[2], initialMargin[2];
    float x, y, z;
    float x1, x2, y1, y2, z1, z2;
};

#endif // COMPUTER_GRAPHICS_OBJECT_HPP
