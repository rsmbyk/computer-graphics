#include <customs/utils/tranform_matrix.hpp>
#include <cstdio>
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

void Object::_transform (mat4 T, int type) {
    transform (T, type);
    _measure ();
}

void Object::_measure () {
    measure ();
    _measureCenter ();
}

void Object::_measureCenter () {
    center[X] = (margin[X][0] + margin[X][1]) / 2;
    center[Y] = (margin[Y][0] + margin[Y][1]) / 2;
    center[Z] = (margin[Z][0] + margin[Z][1]) / 2;
}

void Object::move (GLfloat x, GLfloat y, GLfloat z) {
    mat4 t = translation_matrix (0.1f, 0, 0);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            printf ("%f ", t[i][j]);
        printf ("\n");
    }
    _transform (translation_matrix (x, y, z), TRANSLATE);
}

void Object::rotate (GLfloat x, GLfloat y, GLfloat z) {
    mat4 T0, R, Tb;
    T0 = translation_matrix (-center[X], -center[Y], -center[Z]);
    R = rotation_matrix (x, y, z);
    Tb = translation_matrix (center[X], center[Y], center[Z]);
    _transform (Tb * R * T0, ROTATE);
}

void Object::scale (GLfloat x, GLfloat y, GLfloat z) {
    mat4 T0, S, Tb;
    T0 = translation_matrix (-center[X], -center[Y], -center[Z]);
    S = scaling_matrix (x, y, z);
    Tb = translation_matrix (center[X], center[Y], center[Z]);
    _transform (T0 * S * Tb, SCALE);
}

