#ifndef COMPUTER_GRAPHICS_TRAIN_HPP
#define COMPUTER_GRAPHICS_TRAIN_HPP

#include <customs/shapes/Cylinder.hpp>
#include "Car.hpp"

using namespace std;

class Train : public Thing {
public:
    Train (float x, float y, float z, int length, float carSize);
    void setWalkPath (vector<vec3> path, vec3 pivot, float speed) override;
    void setWalkPath (vector<vec3> path, float speed) override;
    void onWalk (double amount, double deltaTime = DBL_MAX) override;

private:
    float carSize;
    vector<Car*> cars;
    vector<Object*> locomotives;
    Cylinder *chimney;
    
};

#endif // COMPUTER_GRAPHICS_TRAIN_HPP
