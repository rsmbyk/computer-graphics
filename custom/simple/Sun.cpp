#include <custom/shapes/Sphere.hpp>
#include "Sun.hpp"

Sun::Sun (float groundLevel, float groundSize) : Sphere (0, groundLevel+(groundSize/2)+5, 0, 1.5) {
    setColor ({252, 212, 64});
}

void Sun::onRender () {
    rotate ({0, 0, -0.1f}, vec3 ());
    Sphere::onRender ();
}
