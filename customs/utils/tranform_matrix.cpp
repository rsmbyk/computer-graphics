#include "tranform_matrix.hpp"
#include <glm/gtx/quaternion.hpp>

mat4 translation_matrix (float x, float y, float z) {
    return mat4 (1, 0, 0, x,
                 0, 1, 0, y,
                 0, 0, 1, z,
                 0, 0, 0, 1);
}

mat4 translation_matrix (vec3 distance) {
    return translation_matrix (distance.x, distance.y, distance.z);
}

mat4 scaling_matrix (float x, float y, float z) {
    return mat4 (x, 0, 0, 0,
                 0, y, 0, 0,
                 0, 0, z, 0,
                 0, 0, 0, 1);
}

mat4 scaling_matrix (vec3 ratio) {
    return scaling_matrix (ratio.x, ratio.y, ratio.z);
}

mat4 rotation_matrix (float x, float y, float z) {
    x = (float) (x * M_PI / 180.0);
    y = (float) (y * M_PI / 180.0);
    z = (float) (z * M_PI / 180.0);
    vec3 eulerAngles (x, y, z);
    quat rotationQuat (eulerAngles);
    return toMat4 (rotationQuat);
}

mat4 rotation_matrix (vec3 angle) {
    return rotation_matrix (angle.x, angle.y, angle.z);
}
