#ifndef COMPUTER_GRAPHICS_CAR_HPP
#define COMPUTER_GRAPHICS_CAR_HPP

#include <custom/shapes/Box.hpp>
#include <vector>
#include "Thing.hpp"

class Car : public Thing {
public:
    Car (float x, float y, float z, float size);

private:
    Box *box;
    std::vector<Box*> windows;
};

#endif // COMPUTER_GRAPHICS_CAR_HPP
