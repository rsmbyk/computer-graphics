#include "Car.hpp"

#define ms multiplier*size

Car::Car (GLfloat x, GLfloat y, GLfloat z, GLfloat size)
: Object (x-(ms*5), x+(ms*4), y, y+(ms*4), z-(ms*2), z+(ms*2)) {
    box = new Box (x-(ms*4), x+(ms*4), y, y+(ms*4), z-(ms*2), z+(ms*2), true);
    
    connector = new Box (x-(ms*5), x-(ms*4), y+(ms*0.5f), y+(ms*1), z-(ms*0.5f), z+(ms*0.5f));
    for (int i = 0; i < 6; i++)
        connector->setFaceColor (i, Color ());
    connector->setFaceColor (Box::TOP, Color (20, 20, 20, true));
    
    windows.push_back (new Box (x-(ms*1.25f), x+(ms*1.25f), y+(ms*0.75f), y+(ms*3.25f), z+(ms*2), z+(ms*2)+0.05f));
    windows.push_back (new Box (x-(ms*1.25f), x+(ms*1.25f), y+(ms*0.75f), y+(ms*3.25f), z-(ms*2)-0.05f, z-(ms*2)));
    for (int i = 0; i < windows.size (); i++) {
        for (int j = 0; j < 6; j++)
            ((Box*) windows[i])->setFaceColor (j, Color (200, 200, 200, true));
        ((Box*) windows[i])->setFaceColor (Box::FRONT, Color (255, 255, 255, true));
    }
}

void Car::render () {
    box->render ();
    connector->render ();
    for (int i = 0; i < windows.size (); i++)
        windows[i]->render ();
}

void Car::clean () {
    box->clean ();
    connector->clean ();
    for (int i = 0; i < windows.size (); i++)
        windows[i]->clean ();
}

void Car::move (int coord, GLfloat amount) {
    box->move (coord, amount);
    connector->move (coord, amount);
    for (int i = 0; i < windows.size (); i++)
        windows[i]->move (coord, amount);
}

void Car::rotate (GLfloat x, GLfloat y, GLfloat z) {

}

void Car::scale (GLfloat x, GLfloat y, GLfloat z) {

}
