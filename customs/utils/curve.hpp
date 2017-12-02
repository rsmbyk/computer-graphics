#ifndef COMPUTER_GRAPHICS_CURVE_HPP
#define COMPUTER_GRAPHICS_CURVE_HPP

#include <glm/vec3.hpp>
#include <vector>

using namespace glm;
using namespace std;

void bezier_curve (vector<vec3> control_points, vector<vec3> &bezier_points, int flatness);
vec3 de_casteljau (vector<vec3> points, float t);

#endif // COMPUTER_GRAPHICS_CURVE_HPP
