#include "tranform_matrix.hpp"

mat4 translation_matrix (GLfloat x, GLfloat y, GLfloat z) {
    return mat4 (1, 0, 0, x,
                 0, 1, 0, y,
                 0, 0, 1, z,
                 0, 0, 0, 1);
}

mat4 scaling_matrix (GLfloat x, GLfloat y, GLfloat z) {
    return mat4 (x, 0, 0, 0,
                 0, y, 0, 0,
                 0, 0, z, 0,
                 0, 0, 0, 1);
}

mat4 rotation_matrix (GLfloat x, GLfloat y, GLfloat z) {
    x = x * M_PI / 180.0;
    y = y * M_PI / 180.0;
    z = z * M_PI / 180.0;
    vec3 eulerAngles (x, y, z);
    quat rotationQuat (eulerAngles);
    return toMat4 (rotationQuat);
}
