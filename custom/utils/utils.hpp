#ifndef COMPUTER_GRAPHICS_UTILS_HPP
#define COMPUTER_GRAPHICS_UTILS_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <cmath>

#define printVec(vv,nn) for (int ii = 0; ii < (nn); ii++) printf ("%.12f ", (vv)[ii]); printf ("\n");
#define printVec3(vv) printVec ((vv), 3)
#define printVec4(vv) printVec ((vv), 4)
#define printMat(mm,nn) for (int iii = 0; iii < (nn); iii++) { printVec4 ((mm)[iii]); }
#define printMat4(mm) printMat ((mm), 4)

using namespace glm;

namespace grafkom {
    
    #define to_rad_const float (M_PI / 180.0);
    #define to_deg_const float (180.0 / M_PI);
    
    template<typename T> T toDegree (T radian) {
        return radian * to_deg_const;
    }
    
    template<typename T> T toRadian (T degree) {
        return degree * to_rad_const;
    }
    
    float vecLength (vec3 v);
    vec3 between (vec3 a, vec3 b, float t);
    vec3 angleVector (vec3 a, vec3 b);
    
    mat4 translation_matrix (float x, float y, float z);
    mat4 translation_matrix (vec3 distance);
    mat4 scaling_matrix (float x, float y, float z);
    mat4 scaling_matrix (vec3 ratio);
    
    // default rotation order is ZYX
    mat4 rotation_matrix (float x, float y, float z);
    mat4 rotation_matrix (vec3 angle);
    
}

#endif // COMPUTER_GRAPHICS_UTILS_HPP
