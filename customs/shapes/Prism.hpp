#ifndef COMPUTER_GRAPHICS_PRISM_HPP
#define COMPUTER_GRAPHICS_PRISM_HPP

#include <customs/base/Color.hpp>
#include <customs/base/Object.hpp>

class Prism : public Object {
public:
    explicit Prism (bool shuffleColor = false);
    Prism (GLfloat x, GLfloat y, GLfloat z, int n, GLfloat size, GLfloat height, bool shuffleColor = false);
    
    void render () override;
    void clean () override;
    void move (int axis, GLfloat amount) override;
    void rotate (GLfloat x, GLfloat y, GLfloat z) override;
    void scale (GLfloat x, GLfloat y, GLfloat z) override;
    
    Prism *setBaseColor (int slice, Color color);
    Prism *setBaseColor (Color color);
    Prism *setCoverColor (int slice, Color color);
    Prism *setCoverColor (Color color);
    Prism *setSideColor (int slice, Color color);
    Prism *setSideColor (Color color);
    Prism *setColor (int slice, Color color);
    Prism *setRainbowColor ();
    
protected:
    Prism (GLfloat x, GLfloat y, GLfloat z, int n, GLfloat baseSize, GLfloat coverSize, GLfloat height, bool shuffleColor = false);

private:
    GLuint baseaoID {}, baseboID {}, basecboID {};
    GLuint coveraoID {}, coverboID {}, covercboID {};
    GLuint sideaoID {}, sideboID {}, sidecboID {};
    
    GLfloat *side, *base, *cover;
    GLfloat *baseColor, *coverColor, *sideColor;
    int slice;
};

#endif // COMPUTER_GRAPHICS_PRISM_HPP
