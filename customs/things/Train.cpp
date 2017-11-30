#include "Train.hpp"

#define ms Car::multiplier*carSize

Train::Train (GLfloat x, GLfloat y, GLfloat z, int length, GLfloat carSize) {
    for (int i = 1; i <= length; i++) {
        GLfloat xNext = x+(i*9*ms);
        cars.push_back (new Car (xNext, y, z, carSize));
    }
    
    locomotives.push_back (new Box (x, x+(ms*4), y, y+(ms*4), z-(ms*2), z+(ms*2), true));
    auto *cylinder = new Cylinder (x-(ms*2), y-ms/2+ms/4, z, ms*1.5f, ms*4, true);
    cylinder->rotate (0, 0, 90);
    locomotives.push_back ((Object*) cylinder);
    locomotives.push_back (new Box (x-ms*4, x, y, y+ms/4, z-(ms*2), z+(ms*2), true));

    for (Car *car : cars)
        add (car);
    for (Object *box : locomotives)
        add (box);
}
