#ifndef COMPUTER_GRAPHICS_BALL_HPP
#define COMPUTER_GRAPHICS_BALL_HPP

#include <custom/base/Object.hpp>
#include <custom/base/Color.hpp>

class Sphere : public Object {
public:
    Sphere ();
    Sphere (float x, float y, float z, float r);
    void setColor (Color color);

private:
    // pick any reasonable size of θ and ϕ
    // for number of spherical coordinates
    int N1 = 30, N2 = 15;
};

#endif // COMPUTER_GRAPHICS_BALL_HPP
