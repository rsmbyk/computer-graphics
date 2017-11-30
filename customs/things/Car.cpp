#include "Car.hpp"

#define ms multiplier*size

Car::Car (GLfloat x, GLfloat y, GLfloat z, GLfloat size) {
    box = Box (x-(ms*4), x+(ms*4), y, y+(ms*4), z-(ms*2), z+(ms*2), true);
//    box = Box ();

    connector = Box (x-(ms*5), x-(ms*4), y+(ms*0.5f), y+(ms*1), z-(ms*0.5f), z+(ms*0.5f));
    for (int i = 0; i < 6; i++)
        connector.setFaceColor (i, Color ());
    connector.setFaceColor (TOP, Color (20, 20, 20, true));

    windows.push_back (new Box (x-(ms*1.25f), x+(ms*1.25f), y+(ms*0.75f), y+(ms*3.25f), z+(ms*2), z+(ms*2)+0.05f));
    windows.push_back (new Box (x-(ms*1.25f), x+(ms*1.25f), y+(ms*0.75f), y+(ms*3.25f), z-(ms*2)-0.05f, z-(ms*2)));
    for (int i = 0; i < windows.size (); i++) {
        for (int j = 0; j < 6; j++)
            windows[i]->setFaceColor (j, Color (200, 200, 200, true));
        windows[i]->setFaceColor (FRONT, Color (255, 255, 255, true));
    }
    
    add (&box);
    add (&connector);
    for (Box *window : windows)
        add (window);
    _measure ();
}
