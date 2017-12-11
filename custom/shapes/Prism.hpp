#ifndef COMPUTER_GRAPHICS_PRISM_HPP
#define COMPUTER_GRAPHICS_PRISM_HPP

#include <custom/base/Object.hpp>
#include <custom/base/Color.hpp>

using namespace glm;

class Prism : public Object {
public:
    Prism ();
    Prism (float x, float y, float z, int n, float size, float height);
    
    void setBaseColor (int slice, Color color);
    void setBaseColor (Color color);
    void setCoverColor (int slice, Color color);
    void setCoverColor (Color color);
    void setSideColor (int slice, Color color);
    void setSideColor (Color color);
    void setColor (int slice, Color color);
    void setColor (Color color);
    void setRainbowColor ();
    
protected:
    Prism (float x, float y, float z, int n, float baseSize, float coverSize, float height);

private:
    float *cover, *base, *side;
    float *coverColor, *baseColor, *sideColor;
    int slice;
};

#endif // COMPUTER_GRAPHICS_PRISM_HPP
