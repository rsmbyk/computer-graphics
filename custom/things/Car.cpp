#include "Car.hpp"

#define ms multiplier*size

Car::Car (float x, float y, float z, float size) {
    box = Box (x-(ms*4), x+(ms*4), y, y+(ms*4), z-(ms*2), z+(ms*2));
//    box = Box ();

    connector = Box (x-(ms*5), x-(ms*4), y+(ms*0.5f), y+(ms*1), z-(ms*0.5f), z+(ms*0.5f));
    for (int i = 0; i < 6; i++)
        connector.setFaceColor (i, Color ());
    connector.setFaceColor (TOP, {20, 20, 20});

    windows.push_back (new Box (x-(ms*1.25f), x+(ms*1.25f), y+(ms*0.75f), y+(ms*3.25f), z+(ms*2), z+(ms*2)+0.05f));
    windows.push_back (new Box (x-(ms*1.25f), x+(ms*1.25f), y+(ms*0.75f), y+(ms*3.25f), z-(ms*2)-0.05f, z-(ms*2)));
    for (auto &window : windows) {
        for (int j = 0; j < 6; j++)
            window->setFaceColor (j, {200, 200, 200});
        window->setFaceColor (FRONT, {255, 255, 255});
    }
    
    add (&box);
    add (&connector);
    for (Box *window : windows)
        add (window);
    measure ();
}
