#ifndef COMPUTER_GRAPHICS_LOCOMOTIVE_HPP
#define COMPUTER_GRAPHICS_LOCOMOTIVE_HPP

#include <custom/shapes/Box.hpp>
#include <custom/shapes/Cylinder.hpp>
#include "Thing.hpp"

class Locomotive : public Thing {
public:
    Locomotive (float x, float y, float z, float carSize);

private:
    Box *cab;
    Cylinder *nose, *chimney, *dome;
    vector<Cylinder*> tire;
};

#endif // COMPUTER_GRAPHICS_LOCOMOTIVE_HPP
