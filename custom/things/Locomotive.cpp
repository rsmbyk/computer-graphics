#include "Locomotive.hpp"
#include "Train.hpp"

Locomotive::Locomotive (float x, float y, float z, float carSize) {
    float BL, BH, BW;
    BL = Train::L * carSize * 17 / 20;
    BH = Train::H * carSize;
    BW = Train::W * carSize;
    cab = new Box (x-BL/2, x-BL/6, y, y+BH*3/2, z-BW/2, z+BW/2);
    add (cab);
    
    nose = new Cylinder (x-BL/6, y+BH/2, z, BW/2, BL*2/3);
    nose->rotateAt ({0, 0, 90}, {0.5f, 0, 0.5f});
    add (nose);
    
    chimney = new Cylinder ((nose->x1+nose->x)/2, y+BH/2, z, BW/4, BL*2/3);
    add (chimney);
    
    dome = new Cylinder ((nose->x+nose->x2)/2, y+BH/2, z, BW/6, BL*1/3);
    add (dome);
    
    for (int i = 0; i < 3; i++) {
        float r = BL / 12;
        auto left = new Cylinder (nose->x1+r+i*2*BL/9, nose->y1+r, nose->z1, r, 0.05f);
        left->rotate ({-90, 0, 0});
        tire.push_back (left);
        
        auto right = new Cylinder (nose->x1+r+i*2*BL/9, nose->y1+r, nose->z2, r, 0.05f);
        right->rotate ({-90, 0, 0});
        tire.push_back (right);
    }
    
    for (auto t : tire)
        add (t);
    
    init ();
}
