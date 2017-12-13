#ifndef COMPUTER_GRAPHICS_TRAIN_HPP
#define COMPUTER_GRAPHICS_TRAIN_HPP

#include <custom/shapes/Cylinder.hpp>
#include "Locomotive.hpp"
#include "Car.hpp"

using namespace std;

class Train : public Thing {
public:
    Train (float x, float y, float z, int length, float carSize);
    void onSetWalkPath () override;
    void setWalkProgress (int progress);
    void onWalk (double amount) override;
    
    constexpr static float
        L = 0.25f,
        H = 0.1f,
        W = 0.1f;
    
private:
    Locomotive *locomotive;
    vector<Car*> cars;
    float carSize;
};

#endif // COMPUTER_GRAPHICS_TRAIN_HPP
