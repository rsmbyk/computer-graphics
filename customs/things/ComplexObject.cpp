#include "ComplexObject.hpp"

// TODO: calculate ComplexObjectMargin
ComplexObject::ComplexObject ()
: Object (0, 0, 0, 0, 0, 0) {}

void ComplexObject::add (Object *object) {
    objects.push_back (object);
}

void ComplexObject::render () {
    for (int i = 0; i < objects.size (); i++)
        objects[i]->render ();
}

void ComplexObject::clean () {
    for (int i = 0; i < objects.size (); i++)
        objects[i]->clean ();
}

void ComplexObject::move (int coord, GLfloat amount) {
    for (int i = 0; i < objects.size (); i++)
        objects[i]->move (coord, amount);
}

void ComplexObject::rotate (GLfloat x, GLfloat y, GLfloat z) {

}

void ComplexObject::scale (GLfloat x, GLfloat y, GLfloat z) {

}
