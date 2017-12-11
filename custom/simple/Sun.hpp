#ifndef COMPUTER_GRAPHICS_SUN_HPP
#define COMPUTER_GRAPHICS_SUN_HPP

#include "customs/things/Thing.hpp"

class Sun : public Sphere {
public:
    Sun (float groundLevel, float groundSize);
    void onRender () override;
};

#endif // COMPUTER_GRAPHICS_SUN_HPP
