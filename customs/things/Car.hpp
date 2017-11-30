#ifndef COMPUTER_GRAPHICS_CAR_HPP
#define COMPUTER_GRAPHICS_CAR_HPP

#include <vector>
#include <customs/shapes/Box.hpp>
#include "Thing.hpp"

class Car : public Thing {
public:
    Car (GLfloat x, GLfloat y, GLfloat z, GLfloat size);

    static constexpr GLfloat multiplier = 0.1f;

private:
    Box box, connector;
    std::vector<Box*> windows {};
};

#endif // COMPUTER_GRAPHICS_CAR_HPP
