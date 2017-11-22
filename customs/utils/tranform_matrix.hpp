#ifndef COMPUTER_GRAPHICS_TRANFORM_MATRIX_HPP
#define COMPUTER_GRAPHICS_TRANFORM_MATRIX_HPP

#include <glm/gtx/quaternion.hpp>
#include <GL/gl.h>

using namespace glm;

/**
 * !!! IMPORTANT NOTES !!!
 *
 * use vec4: (x, y, z, w)
 * w == 1 --> vec4 is a position in space.
 * w == 0 --> vec4 is a direction.
 */

const mat4 TRANSLATION_MATRIX = {
    1, 0, 0, 0, // 1, 0, 0, x,
    0, 1, 0, 0, // 0, 1, 0, y,
    0, 0, 1, 0, // 0, 0, 1, z,
    0, 0, 0, 1  // 0, 0, 0, 1
};

const mat4 SCALING_MATRIX = {
    0, 0, 0, 0, // x, 0, 0, 0,
    0, 0, 0, 0, // 0, y, 0, 0,
    0, 0, 0, 0, // 0, 0, z, 0,
    0, 0, 0, 1  // 0, 0, 0, 1
};

const mat4 IDENTITY_MATRIX = {
    1, 0, 0, 0, // 1, 0, 0, 0,
    0, 1, 0, 0, // 0, 1, 0, 0,
    0, 0, 1, 0, // 0, 0, 1, 0,
    0, 0, 0, 1  // 0, 0, 0, 1
};

mat4 translation_matrix (GLfloat x, GLfloat y, GLfloat z);
mat4 scaling_matrix (GLfloat x, GLfloat y, GLfloat z);
mat4 rotation_matrix (GLfloat x, GLfloat y, GLfloat z);

#endif // COMPUTER_GRAPHICS_TRANFORM_MATRIX_HPP
