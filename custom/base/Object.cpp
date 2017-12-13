#include <glew.h>
#include <glfw3.h>
#include <glm/gtx/quaternion.hpp>
#include <glm/vec3.hpp>
#include <custom/utils/utils.hpp>
#include <cstdio>
#include "Object.hpp"

using namespace glm;
using namespace grafkom;

Object::Object () {
    TRIANGLE_COUNT = 1;
    BUFFER_LENGTH = TRIANGLE_COUNT * 3;
    BUFFER_SIZE = BUFFER_LENGTH * sizeof (float*);
    buffer = new float[BUFFER_LENGTH];
}

void Object::onInit () {
    glGenVertexArrays (1, &vaoID);
    glBindVertexArray (vaoID);
    glGenBuffers (1, &vboID);
    glBindBuffer (GL_ARRAY_BUFFER, vboID);
    glBufferData (GL_ARRAY_BUFFER, BUFFER_SIZE, buffer, GL_STATIC_DRAW);
    
    // Initial color for all faces of the box is black.
    // It can be overridden by calling @setFaceColor method.
    colors = new float[BUFFER_LENGTH];
    for (int i = 0; i < BUFFER_LENGTH; i++)
        colors[i] = 0.0f;
    
    // if size parameter of glBufferData didn't use sizeof (),
    // it has to be length of color array multiplied by 4.
    // Still figuring out what this number (4) means. \:
    //
    // EDIT: confirmed, lol :p. 4 is length of bit of its data
    //       type.
    glGenBuffers (1, &cboID);
    glBindBuffer (GL_ARRAY_BUFFER, cboID);
    glBufferData (GL_ARRAY_BUFFER, BUFFER_SIZE, colors, GL_STATIC_DRAW);
}

void Object::init () {
    onInit ();
    measure ();
    lastRenderTime = glfwGetTime ();
    
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            initialMargin[i][j] = margin[i][j];
    for (int i = 0; i < 3; i++)
        initialCenter[i] = center[i];
}

void Object::onMeasureMargin () {
    for (int i = 0; i < BUFFER_LENGTH; i += 3)
        for (int j = 0; j < 3; j++) {
            margin[0][j] = std::min (margin[0][j], buffer[i+j]);
            margin[1][j] = std::max (margin[1][j], buffer[i+j]); }
}

void Object::measureMargin () {
    for (int i = 0; i < 3; i++)
        margin[1][i] = - (margin[0][i] = FLT_MAX);
    
    onMeasureMargin ();
    
    x1 = margin[0][X];
    x2 = margin[1][X];
    y1 = margin[0][Y];
    y2 = margin[1][Y];
    z1 = margin[0][Z];
    z2 = margin[1][Z];
}

void Object::measureCenter () {
    x = center.x = (margin[0][X] + margin[1][X]) / 2;
    y = center.y = (margin[0][Y] + margin[1][Y]) / 2;
    z = center.z = (margin[0][Z] + margin[1][Z]) / 2;
}

void Object::measure () {
    measureMargin ();
    measureCenter ();
}

void Object::onRender () {
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    
    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, cboID);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    
    glDrawArrays (GL_TRIANGLES, 0, TRIANGLE_COUNT);
    
    glDisableVertexAttribArray (0);
    glDisableVertexAttribArray (1);
}

void Object::render () {
    onRender ();
    lastRenderTime = glfwGetTime ();
}

void Object::updateBuffer () {
    glBindBuffer (GL_ARRAY_BUFFER, vboID);
    glBufferData (GL_ARRAY_BUFFER, BUFFER_SIZE, buffer, GL_STATIC_DRAW);
    glBindBuffer (GL_ARRAY_BUFFER, cboID);
    glBufferData (GL_ARRAY_BUFFER, BUFFER_SIZE, colors, GL_STATIC_DRAW);
}

void Object::onClean () {
    glDeleteVertexArrays (1, &vaoID);
    glDeleteBuffers (1, &vboID);
    glDeleteBuffers (1, &cboID);
}

void Object::clean () {
    onClean ();
}

void Object::onTransform (mat4 T) {
    for (int i = 0; i < BUFFER_LENGTH; i += 3) {
        vec4 res = vec4 (buffer[i], buffer[i+1], buffer[i+2], 1) * T;
        for (int j = 0; j < 3; j++)
            buffer[i+j] = res[j];
    }
    
    updateBuffer ();
}

void Object::transform (mat4 T) {
    transform_matrix *= T;
    onTransform (T);
    measure ();
}

void Object::translate (vec3 v) {
    translationDistance += v;
    transform (translation_matrix (v));
}

void Object::translateTo (vec3 to, vec3 shift) {
    translateTo (to - (shift - center));
}

void Object::translateTo (vec3 to) {
    translate (to - center);
}

void Object::rotate (quat rotation, vec3 centerOfRotation) {
    rotationQuat *= rotation;
    mat4 T0, R, Tb, wlr;
    T0 = translation_matrix (-centerOfRotation);
    R  = toMat4 (rotation);
    Tb = translation_matrix (centerOfRotation);
    transform (T0 * R * Tb);
}

void Object::rotateAt (quat rotation, vec3 pivot) {
    rotate (rotation, getPivot (pivot));
}

void Object::rotate (quat rotation) {
    rotate (rotation, center);
}

void Object::rotate (vec3 angle, vec3 centerOfRotation) {
    rotate (quat (toRadian (angle)), centerOfRotation);
}

void Object::rotateAt (vec3 angle, vec3 pivot) {
    rotate (angle, getPivot (pivot));
}

void Object::rotate (vec3 angle) {
    rotate (angle, center);
}

void Object::rotateTo (quat rotation, vec3 centerOfRotation) {
    rotateReset ();
    rotate (rotation, centerOfRotation);
}

void Object::rotateToAt (quat rotation, vec3 pivot) {
    rotateTo (rotation, getPivot (pivot));
}

void Object::rotateTo (quat rotation) {
    rotateTo (rotation, center);
}

void Object::rotateTo (vec3 angle, vec3 centerOfRotation) {
    rotateTo (quat (toRadian (angle)), centerOfRotation);
}

void Object::rotateToAt (vec3 angle, vec3 pivot) {
    rotateTo (angle, getPivot (pivot));
}

void Object::rotateTo (vec3 angle) {
    rotateTo (angle, center);
}

void Object::rotateReset () {
    rotate (inverse (rotationQuat));
}

void Object::scaleTo (vec3 ratio, vec3 scalingCenter) {
    scaleRatio *= ratio;
    mat4 T0, S, Tb;
    T0 = translation_matrix (-scalingCenter);
    S  = scaling_matrix (ratio);
    Tb = translation_matrix (scalingCenter);
    transform (T0 * S * Tb);
}

void Object::scaleToAt (vec3 ratio, vec3 pivot) {
    scaleTo (ratio, getPivot (pivot));
}

void Object::scaleTo (vec3 ratio) {
    scaleTo (ratio, center);
}

void Object::scale (vec3 ratio, vec3 scalingCenter) {
    scaleTo (ratio + 1.0f, scalingCenter);
}

void Object::scaleAt (vec3 ratio, vec3 pivot) {
    scale (ratio, getPivot (pivot));
}

void Object::scale (vec3 ratio) {
    scale (ratio, center);
}

vec3 Object::getInitialPivot (vec3 pivot) {
    for (int i = 0; i < 3; i++)
        if (pivot[i] < 0 || pivot[i] > 1)
            return center;
    
    vec3 *m = initialMargin;
    vec3 coord;
    for (int i = 0; i < 3; i++)
        coord[i] = m[0][i] + (m[1][i] - m[0][i]) * pivot[i];
    return coord;
}

vec3 Object::getPivot (vec3 pivot) {
    vec4 p (vec4 (getInitialPivot (pivot), 1) * transform_matrix);
    return vec3 (p.x, p.y, p.z);
}

void Object::setWalkPath (vector<vec3> path, vec3 pivot, float speed) {
    walkPath = std::move (path);
    walkPivot = pivot;
    walkSpeed = speed;
    onSetWalkPath ();
    walkLastTime = glfwGetTime ();
}

void Object::setWalkPath (vector<vec3> path, float speed) {
    setWalkPath (std::move (path), vec3 (0.5f, 0.5f, 0.5f), speed);
}

/***
 * this method invoked after object has been positioned in first
 * control point and is looking towards second control point.
 */
void Object::onSetWalkPath () {
    setWalkProgress (0);
}

vec3 Object::getWalkPoint (int i) {
    return walkPath[i] + center - getPivot (walkPivot);
}

void Object::walk () {
    if (walkPath.empty ())
        return;
    
    double currentTime = glfwGetTime ();
    double deltaTime = currentTime - walkLastTime;
    walkLastTime = glfwGetTime ();
    
    double amount = deltaTime * walkSpeed;
    onWalk (amount);
}

void Object::setWalkProgress (int progress) {
    if (progress >= walkPath.size ())
        return;

    walkProgress = progress;
    walkNext = (walkProgress + 1) % walkPath.size ();
    
    translateTo (getWalkPoint (walkProgress));
    rotate (inverse (rotationQuat));
    vec3 angle = angleVector (getWalkPoint (walkProgress), getWalkPoint (walkNext));
    rotate (quat (toRadian (angle)));
}

void Object::onWalk (double amount) {
    vec3 to = center;
    
    while (amount > 0.0) {
        vec3 next = getWalkPoint (walkNext);
        float len = vecLength (next - to);
        
        if (len <= amount) {
            do {
                walkProgress = walkNext;
                walkNext = (walkNext + 1) % walkPath.size ();
            }
            while (walkPath[walkProgress] == walkPath[walkNext]);
    
            amount -= len;
            to = next;
            setWalkProgress (walkProgress);
        }
        else {
            // u: unit vector
            vec3 v = next - to;
            vec3 u = v / vecLength (v);
            to = to + (u * float (amount));
            break;
        }
    }
    
    translateTo (to);
}
