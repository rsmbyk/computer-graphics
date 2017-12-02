#include <GL/glew.h>
#include <glfw3.h>
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <customs/utils/tranform_matrix.hpp>
#include "Object.hpp"

using namespace glm;
using namespace std;

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
    lastRenderTime = translateToLastTime = glfwGetTime ();
    translateToTarget = center;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            initialMargin[i][j] = margin[i][j];
    for (int i = 0; i < 3; i++)
        initialCenter[i] = center[i];
}

void Object::onMeasureMargin () {
    for (int i = 0; i < BUFFER_LENGTH; i += 3)
        for (int j = 0; j < 3; j++) {
            margin[0][j] = min (margin[0][j], buffer[i+j]);
            margin[1][j] = max (margin[1][j], buffer[i+j]); }
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
    transform_matrix = transform_matrix * T;
    onTransform (T);
    measure ();
}

void Object::translate (vec3 v) {
    translationDistance += v;
    transform (translation_matrix (v));
}

void Object::translateTo (vec3 to, float speed) {
    if (translateToTarget != to) {
        translateToTarget = to;
        translateToDiff = to - center;
    }
    
    if (center == translateToTarget)
        return;
    
    double r = sqrt (sqrt (pow (translateToDiff.x, 2) + pow (translateToDiff.z, 2)) + pow (translateToDiff.y, 2));
    double currentTime = glfwGetTime ();
    double time = currentTime - translateToLastTime;
    translateToLastTime = currentTime;
    
    auto totalTime =  (float) (r) / speed;
    auto total = (float) (time) / totalTime;
    
    vec3 amount = translateToDiff * total;
    vec3 dist = to - center;
    vec3 move;
    
    if (fabsf (amount.x) < fabsf (dist.x)) move.x = amount.x;
    else move.x = dist.x;
    
    if (fabsf (amount.y) < fabsf (dist.y)) move.y = amount.y;
    else move.y = dist.y;
    
    if (fabsf (amount.z) < fabsf (dist.z)) move.z = amount.z;
    else move.z = dist.z;
    
    translate (move);
}

void Object::orbit (vec3 angle, vec3 orbitCenter) {
    mat4 T0, R, Tb;
    T0 = translation_matrix (-orbitCenter);
    R  = rotation_matrix (angle);
    Tb = translation_matrix (orbitCenter);
    rotationAngle += angle;
    transform (T0 * R * Tb);
}

void Object::rotateAt (vec3 angle, vec3 centerOfRotation) {
    vec3 coordinate = getCoordinate (centerOfRotation);
    vec4 orbitCenter = vec4 (coordinate, 1) * transform_matrix;
    orbit (angle, vec3 (orbitCenter.x, orbitCenter.y, orbitCenter.z));
}

void Object::rotate (vec3 angle) {
    orbit (angle, center);
}

void Object::scale (vec3 ratio, vec3 scalingCenter) {
    scaleRatio += ratio;
    mat4 T0, S, Tb;
    T0 = translation_matrix (-scalingCenter);
    S  = scaling_matrix (ratio);
    Tb = translation_matrix (scalingCenter);
    transform (T0 * S * Tb);
}

void Object::scaleToAt (vec3 ratio, vec3 scalingCenter) {
    scale (ratio, getCoordinate (scalingCenter));
}

void Object::scaleAt (vec3 ratio, vec3 scalingCenter) {
    scaleToAt (ratio + 1.0f, scalingCenter);
}

void Object::scaleTo (vec3 ratio) {
    scale (ratio, center);
}

void Object::scaleBy (vec3 ratio) {
    scaleTo (ratio + 1.0f);
}

vec3 Object::getCoordinate (vec3 centralCoordinates) {
    vec3 coordinate;
    coordinate.x = initialMargin[0][X] + (initialMargin[1][X] - initialMargin[0][X]) * centralCoordinates.x;
    coordinate.y = initialMargin[0][Y] + (initialMargin[1][Y] - initialMargin[0][Y]) * centralCoordinates.y;
    coordinate.z = initialMargin[0][Z] + (initialMargin[1][Z] - initialMargin[0][Z]) * centralCoordinates.z;
    return coordinate;
}

