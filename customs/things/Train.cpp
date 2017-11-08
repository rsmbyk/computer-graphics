#include "Train.hpp"

// TODO: calculate train margins
Train::Train (GLfloat x, GLfloat y, GLfloat z, int length, GLfloat carSize)
: Object (0, 0, 0, 0, 0, 0) {
    for (int i = 1; i <= length; i++) {
        GLfloat xNext = x+(i*Car::multiplier*9*carSize);
        cars.push_back (new Car (xNext, y, z, carSize));
    }
}

void Train::render () {
//    chimney.render ();
    for (int i = 0; i < cars.size (); i++)
        cars[i]->render ();
}

void Train::clean () {
//    chimney.clean ();
    for (int i = 0; i < cars.size (); i++)
        cars[i]->clean ();
}

void Train::move (int coord, GLfloat amount) {
//    chimney->move (coord, amount);
    for (int i = 0; i < cars.size (); i++)
        cars[i]->move (coord, amount);
}

void Train::rotate (GLfloat x, GLfloat y, GLfloat z) {

}

void Train::scale (GLfloat x, GLfloat y, GLfloat z) {

}
