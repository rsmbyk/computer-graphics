#include <glm/gtx/quaternion.hpp>
#include <custom/base/Object.hpp>
#include <cstdio>
#include "utils.hpp"



namespace grafkom {

    
    
    float vecLength (vec3 v) {
        return sqrtf (v.x * v.x + v.z * v.z + v.y * v.y);
    }
    
    vec3 between (vec3 a, vec3 b, float t) {
        return (a * (1-t)) + (b * t);
    }
    
    vec3 angleVector (vec3 a, vec3 b) {
        vec3 angle;
        vec3 c = b - a;
        float r = sqrtf (c.x * c.x + c.z * c.z);
        
        angle.x = 0;
        angle.y = atan (c.z / c.x);
        angle.z = -atan (c.y / r);
        angle = toDegree (angle);
        
        if (c.x < 0)
            angle += vec3 (0, 180, 0);
        
        return angle;
    }
    
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
        return rotation_matrix ({x, y, z});
    }
    
    mat4 rotation_matrix (vec3 angle) {
        return toMat4 (quat (toDegree (angle)));
    }
}
