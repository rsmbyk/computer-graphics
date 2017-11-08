#ifndef COMPUTER_GRAPHICS_TRAIN_HPP
#define COMPUTER_GRAPHICS_TRAIN_HPP

#include <customs/shapes/Cylinder.hpp>
#include "Car.hpp"

class Train : public Object {
public:
    Train (GLfloat x, GLfloat y, GLfloat z, int length, GLfloat carSize);
    
    void render () override;
    void clean () override;
    void move (int coord, GLfloat amount) override;
    void rotate (GLfloat x, GLfloat y, GLfloat z) override;
    void scale (GLfloat x, GLfloat y, GLfloat z) override;

private:
    std::vector<Car*> cars {};
    Cylinder *chimney {};
};

#endif // COMPUTER_GRAPHICS_TRAIN_HPP
