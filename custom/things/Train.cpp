#include <cstdio>
#include <custom/utils/utils.hpp>
#include "Train.hpp"

using namespace grafkom;

Train::Train (float x, float y, float z, int length, float carSize) {
    this->carSize = carSize;
    
    locomotive = new Locomotive (x, y, z, carSize);
    add (locomotive);
    
    for (int i = 1; i <= length; i++) // NOLINT
        cars.push_back (new Car (x-(i*L*carSize), y, z, carSize));
    
    for (auto car : cars)
        add (car);
    
    init ();
}

void Train::onSetWalkPath () {
    for (int i = 0; i < cars.size (); i++) {
        cars[i]->setWalkPath (walkPath, {0.5f, 0, 0.5f}, walkSpeed);
        cars[i]->onWalk ((i+1) * L * carSize);
    }
    
    locomotive->setWalkPath (walkPath, {0.5f, 0, 0.5f}, walkSpeed);
    locomotive->onWalk ((cars.size ()+1) * L * carSize);
    walkProgress = locomotive->walkProgress;
    walkNext = locomotive->walkNext;
    measure ();
}

void Train::onWalk (double amount) {
    for (auto car : cars)
        car->onWalk (amount);
    locomotive->onWalk (amount);
    walkProgress = locomotive->walkProgress;
    walkNext = locomotive->walkNext;
    measure ();
}

void Train::setWalkProgress (int progress) {
    for (int i = 0; i < cars.size (); i++) {
        cars[i]->setWalkProgress (progress);
        cars[i]->onWalk ((i+1) * L * carSize);
    }
    
    locomotive->setWalkProgress (progress);
    locomotive->onWalk ((cars.size ()+1) * L * carSize);
    walkProgress = locomotive->walkProgress;
    walkNext = locomotive->walkNext;
    measure ();
}
