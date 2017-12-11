#include "Plane.hpp"

Plane::Plane (float groundLevel, float groundSize)
: Box (-groundSize/2, groundSize/2, groundLevel-0.2f, groundLevel, -groundSize/2, groundSize/2) {
    setColor ({81, 66, 55});
    setFaceColor (TOP, {109, 88, 74});
    setFaceColor (BOTTOM, {60, 49, 41});
}
