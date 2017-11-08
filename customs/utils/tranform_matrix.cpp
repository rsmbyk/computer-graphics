#include "tranform_matrix.hpp"

glm::mat4 build_translation_matrix (GLfloat *arr) {
    glm::mat4 matrix (TRANSLATION_MATRIX);
    for (int i = 0; i < 3; i++)
        matrix[i][3] = arr[i];
    return matrix;
}

glm::mat4 build_translation_matrix (GLfloat x, GLfloat y, GLfloat z) {
    return build_translation_matrix (new GLfloat[3] {x, y, z});
}

glm::mat4 build_scaling_matrix (GLfloat *arr) {
    glm::mat4 matrix (SCALING_MATRIX);
    for (int i = 0; i < 3; i++)
        matrix[i][i] = arr[i];
    return matrix;
}

glm::mat4 build_scaling_matrix (GLfloat x, GLfloat y, GLfloat z) {
    return build_scaling_matrix (new GLfloat[3] {x, y, z});
}

glm::mat4 build_rotation_matrix (GLfloat x, GLfloat y, GLfloat z) {
    glm::vec3 eulerAngles (x, y, z);
    glm::quat rotationQuat (eulerAngles);
    return glm::toMat4 (rotationQuat);
}
