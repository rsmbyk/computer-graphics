#ifndef COMPUTER_GRAPHICS_SUN_HPP
#define COMPUTER_GRAPHICS_SUN_HPP

#include "Thing.hpp"

class Sun : public Thing {
public:
    Sun (GLfloat groundLevel, GLfloat groundSize);
    void render () override;

private:
    Sphere sun;
};

#endif // COMPUTER_GRAPHICS_SUN_HPP
