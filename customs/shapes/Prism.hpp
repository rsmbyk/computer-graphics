#ifndef COMPUTER_GRAPHICS_PRISM_HPP
#define COMPUTER_GRAPHICS_PRISM_HPP

#include <customs/base/Color.hpp>
#include <customs/base/Object.hpp>

using namespace glm;

class Prism : public Object {
public:
    Prism ();
    Prism (GLfloat x, GLfloat y, GLfloat z, int n, GLfloat size, GLfloat height, bool shuffleColor = false);
    
    void render () override;
    void clean () override;
    void transform (mat4 T, int type) override;
    void measure () override;
    
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
    GLuint coveraoID, coverboID, covercboID;
    GLuint baseaoID, baseboID, basecboID;
    GLuint sideaoID, sideboID, sidecboID;
    
    GLfloat *cover, *base, *side;
    GLfloat *coverColor, *baseColor, *sideColor;
    GLint slice;
    GLint EDGE_LENGTH, EDGE_SIZE, SIDE_LENGTH, SIDE_SIZE;
};

#endif // COMPUTER_GRAPHICS_PRISM_HPP
