#include <cstdlib>
#include "Color.hpp"

#define randOrZero (shuffleColor ? (GLfloat) rand () / (GLfloat) RAND_MAX : 0) // NOLINT

Color::Color (bool shuffleColor) {
    r = randOrZero;
    g = randOrZero;
    b = randOrZero;
}

Color::Color (GLfloat r, GLfloat g, GLfloat b, bool hex) {
    if (hex) set (r/255, g/255, b/255);
    else set (r, g, b);
}

void Color::set (GLfloat r, GLfloat g, GLfloat b) {
    this->r = r;
    this->g = g;
    this->b = b;
}
