#include <customs/utils/tranform_matrix.hpp>
#include <cstdio>
#include "Object.hpp"

using namespace glm;

Object::Object (GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2) {
    x = center[X] = (x1 + x2) / 2;
    y = center[Y] = (y1 + y2) / 2;
    z = center[Z] = (z1 + z2) / 2;
    this->x1 = margin[X][0] = x1;
    this->x2 = margin[X][1] = x2;
    this->y1 = margin[Y][0] = y1;
    this->y2 = margin[Y][1] = y2;
    this->z1 = margin[Z][0] = z1;
    this->z2 = margin[Z][1] = z2;
}

void Object::_transform (mat4 T, int type) {
    transform (T, type);
    _measure ();
}

void Object::_measure () {
    measure ();
    _measureMargin ();
    _measureCenter ();
}

void Object::_measureCenter () {
    x = center[X] = (margin[X][0] + margin[X][1]) / 2;
    y = center[Y] = (margin[Y][0] + margin[Y][1]) / 2;
    z = center[Z] = (margin[Z][0] + margin[Z][1]) / 2;
}

void Object::_measureMargin () {
    x1 = margin[X][0];
    x2 = margin[X][1];
    y1 = margin[Y][0];
    y2 = margin[Y][1];
    z1 = margin[Z][0];
    z2 = margin[Z][1];
}

void Object::translate (GLfloat x, GLfloat y, GLfloat z) {
    _transform (translation_matrix (x, y, z), TRANSLATE);
}

void Object::rotate (GLfloat x, GLfloat y, GLfloat z) {
    orbit (x, y, z, this->x, this->y, this->z);
}

void Object::orbit (GLfloat x, GLfloat y, GLfloat z, GLfloat xCenter, GLfloat yCenter, GLfloat zCenter) {
    mat4 T0, R, Tb;
    T0 = translation_matrix (-xCenter, -yCenter, -zCenter);
    R  = rotation_matrix (x, y, z);
    Tb = translation_matrix (xCenter, yCenter, zCenter);
    _transform (T0 * R * Tb, ROTATE);
}

void Object::scale (GLfloat x, GLfloat y, GLfloat z) {
    scaleTo (1+x, 1+y, 1+z);
}

void Object::scaleTo (GLfloat x, GLfloat y, GLfloat z) {
    mat4 T0, S, Tb;
    T0 = translation_matrix (-this->x, -this->y, -this->z);
    S  = scaling_matrix (x, y, z);
    Tb = translation_matrix (this->x, this->y, this->z);
    _transform (T0 * S * Tb, SCALE);
}

