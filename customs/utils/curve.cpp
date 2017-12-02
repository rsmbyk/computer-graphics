#include <cmath>
#include "curve.hpp"

using namespace std;

vec3 get_angle (vec3 a, vec3 b) {
    vec3 angle;
    vec3 c = b - a;
    float r = sqrt (c.x * c.x + c.y * c.y);
    angle.x = atan (r / c.y);
    angle.y = atan (c.z / c.x);
//    angle.z = atan ()
    return a;
}

vec3 de_casteljau (vector<vec3> points, float t) {
    if (points.size () == 1)
        return points[0];
    
    vector<vec3> p;
    for (int i = 0; i < points.size () - 1; i++) {
        vec3 p1 = points[i] * (1-t);
        vec3 p2 = points[i+1] * t;
        p.push_back (p1 + p2);
    }
    
    return de_casteljau (p, t);
}

void bezier_curve (vector<vec3> &control_points, vector<vec3> &bezier_points, int flatness) {
    flatness = std::min (flatness, 100);
    for (int i = 0; i <= flatness; i++)
        bezier_points.push_back (de_casteljau (control_points, 100.0f / flatness * i));
}
