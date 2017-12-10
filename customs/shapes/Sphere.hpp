#ifndef COMPUTER_GRAPHICS_BALL_HPP
#define COMPUTER_GRAPHICS_BALL_HPP

#include <customs/base/Object.hpp>
#include <customs/base/Color.hpp>

class Sphere : public Object {
public:
    Sphere ();
    Sphere (float x, float y, float z, float r);
    
    void setColor (Color color);

private:
    // pick any reasonable size of θ and ϕ
    // for number of spherical coordinates
    int N1 = 45, N2 = 15;
};

#endif // COMPUTER_GRAPHICS_BALL_HPP
