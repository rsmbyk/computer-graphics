#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <glm/glm.hpp>
using namespace glm;

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif
