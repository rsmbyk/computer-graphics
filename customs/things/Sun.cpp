#include <customs/shapes/Sphere.hpp>
#include "Sun.hpp"

Sun::Sun (GLfloat groundLevel, GLfloat groundSize) {
    sun = Sphere (0, groundLevel+(groundSize/2)+5, 0, 1.5);
    add (&sun);
    _measure ();
}

void Sun::render () {
    sun.orbit (0, 0, 0.5f, 0, 0, 0);
    Thing::render ();
}

