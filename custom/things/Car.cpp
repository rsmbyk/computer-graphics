#include "Car.hpp"
#include "Train.hpp"

Car::Car (float x, float y, float z, float size) {
    float BL, BH, BW;
    BL = Train::L * size * 17 / 20;
    BH = Train::H * size;
    BW = Train::W * size;
    box = new Box (x-BL/2, x+BL/2, y, y+BH, z-BW/2, z+BW/2);
    
    float WL, WH, WW;
    WL = BL / 4;
    WH = BH / 2;
    WW = BW / 50;
    windows.push_back (new Box (x-WL/2, x+WL/2, y+BH/4, y+BH/4+WH, z-BW/2-WW, z-BW/2));
    windows.push_back (new Box (x-WL/2, x+WL/2, y+BH/4, y+BH/4+WH, z+BW/2, z+BW/2+WW));
    
    for (auto window : windows) {
        for (int j = 0; j < 6; j++)
            window->setFaceColor (j, {200, 200, 200});
        window->setFaceColor (FRONT, {255, 255, 255});
    }
    
    add (box);
    for (auto window : windows)
        add (window);
    
    init ();
}
