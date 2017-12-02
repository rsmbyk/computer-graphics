#ifndef COMPUTER_GRAPHICS_TRANFORM_MATRIX_HPP
#define COMPUTER_GRAPHICS_TRANFORM_MATRIX_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

using namespace glm;

/**
 * !!! IMPORTANT NOTES !!!
 *
 * use vec4: (x, y, z, w)
 * w == 1 --> vec4 is a position in space.
 * w == 0 --> vec4 is a direction.
 */

mat4 translation_matrix (float x, float y, float z);
mat4 translation_matrix (vec3 distance);
mat4 scaling_matrix (float x, float y, float z);
mat4 scaling_matrix (vec3 ratio);
mat4 rotation_matrix (float x, float y, float z);
mat4 rotation_matrix (vec3 angle);

#endif // COMPUTER_GRAPHICS_TRANFORM_MATRIX_HPP
