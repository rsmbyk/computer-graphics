#include "vector_operations.hpp"
#include <cmath>
#include <customs/base/Object.hpp>
#include <cstdio>

using namespace glm;
using namespace std;

namespace grafkom {
    double length (vec3 v) {
        return sqrt (pow (v.x, 2) + pow (v.z, 2) + pow (v.y, 2));
    }
    
    vec3 between (vec3 a, vec3 b, float t) {
        return (a * (1-t)) + (b * t);
    }
    
    vec3 angleVector (vec3 a, vec3 b) {
        vec3 angle;
        vec3 c = b - a;
        float r = sqrt (c.x * c.x + c.z * c.z);
        angle.x = 0;
        angle.y = (float) (atan (c.z / c.x) * 180.0 / M_PI);
        angle.z = (float) (-atan (c.y / r) * 180.0 / M_PI);
        return angle;
    }
}
