#ifndef COMPUTER_GRAPHICS_CAR_HPP
#define COMPUTER_GRAPHICS_CAR_HPP

#include <custom/shapes/Box.hpp>
#include <vector>
#include "Thing.hpp"

class Car : public Thing {
public:
    Car (float x, float y, float z, float size);
    static constexpr float multiplier = 0.1f;

private:
    Box box, connector;
    std::vector<Box*> windows {};
};

#endif // COMPUTER_GRAPHICS_CAR_HPP
