#include <glfw3.h>
#include <cstdio>
#include "Train.hpp"

#define ms Car::multiplier*carSize

Train::Train (float x, float y, float z, int length, float carSize) {
    this->carSize = carSize;
    for (int i = 1; i <= length; i++) {
        float xNext = x+(i*9*ms);
        cars.push_back (new Car (xNext, y, z, carSize));
    }
    
    locomotives.push_back (new Box (x, x+(ms*4), y, y+(ms*4), z-(ms*2), z+(ms*2)));
    auto *cylinder = new Cylinder (x-(ms*2), y-ms/2+ms/4, z, ms*1.5f, ms*4);
    cylinder->rotate ({0, 0, 90});
    locomotives.push_back ((Object*) cylinder);
    locomotives.push_back (new Box (x-ms*4, x, y, y+ms/4, z-(ms*2), z+(ms*2)));

    for (Car *car : cars)
        add (car);
//    for (Object *box : locomotives)
//        add (box);
}

void Train::setWalkPath (vector<vec3> path, vec3 pivot, float speed) {
    Object::setWalkPath (path, pivot, speed);
    for (int i = cars.size () - 1, j = 0; i >= 0; i--, j++) {
        cars[i]->setWalkPath (path, {0.5f, 0, 0.5f}, speed);
        cars[i]->walkProgress = walkProgress;
        cars[i]->onWalk (j * 9 * ms);
        walkProgress = cars[i]->walkProgress;
    }
}

void Train::setWalkPath (vector<vec3> path, float speed) {
    Object::setWalkPath (path, speed);
}

void Train::onWalk (double amount, double deltaTime) {
    for (Car *car : cars) {
        car->onWalk (amount, deltaTime);
    }
}
