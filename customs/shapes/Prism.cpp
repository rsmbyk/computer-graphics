#include <algorithm>
#include <cmath>
#include <GL/glew.h>
#include <customs/base/Coord.hpp>
#include "Prism.hpp"

Prism::Prism (bool shuffleColor)
: Prism (0, 0, 0, 5, 2, 4, shuffleColor) {}

Prism::Prism (GLfloat x, GLfloat y, GLfloat z, int n, GLfloat size, GLfloat height, bool shuffleColor)
: Prism (x, y, z, n, size, size, height, shuffleColor) {}

// maximum size between base and cover to calculate margin size
#define maxSize std::max (baseSize, coverSize)
Prism::Prism (GLfloat x, GLfloat y, GLfloat z, int n, GLfloat baseSize, GLfloat coverSize, GLfloat height, bool shuffleColor)
: Object (x-maxSize, x+maxSize, y, y+height, z-maxSize, z+maxSize) {
    if (n > 360) n = 360;
    slice = n;
    
    side = new GLfloat[slice*18];
    base = new GLfloat[slice*9];
    cover = new GLfloat[slice*9];
    
    GLfloat y1, y2;
    y1 = y;
    y2 = y + height;
    
    for (int i = 0; i < slice; i++) {
        double a1, a2;
        a1 = i * (2 * M_PI / slice);
        a2 = ((i+1) % slice) * (2 * M_PI / slice);
        
        GLfloat x1, x2, x3, x4, z1, z2, z3, z4;
        x1 = (GLfloat) (x + baseSize * cos (a1));
        z1 = (GLfloat) (z + baseSize * sin (a1));
        x2 = (GLfloat) (x + baseSize * cos (a2));
        z2 = (GLfloat) (z + baseSize * sin (a2));
        x3 = (GLfloat) (x + coverSize * cos (a1));
        z3 = (GLfloat) (z + coverSize * sin (a1));
        x4 = (GLfloat) (x + coverSize * cos (a2));
        z4 = (GLfloat) (z + coverSize * sin (a2));
        
        // 32
        // 01
        Coord v[4];
        v[0].set (x1, y1, z1);
        v[1].set (x2, y1, z2);
        v[2].set (x4, y2, z4);
        v[3].set (x3, y2, z3);
        
        GLfloat *s;
        s = &base[i*9];
        s[0] = x, s[1] = y1, s[2] = z;
        s[3] = v[0].x, s[4] = v[0].y, s[5] = v[0].z;
        s[6] = v[1].x, s[7] = v[1].y, s[8] = v[1].z;
        
        s = &cover[i*9];
        s[0] = x, s[1] = y2, s[2] = z;
        s[3] = v[2].x, s[4] = v[2].y, s[5] = v[2].z;
        s[6] = v[3].x, s[7] = v[3].y, s[8] = v[3].z;
        
        s = &side[i*18];
        s[0] = v[3].x, s[1] = v[3].y, s[2] = v[3].z;
        s[3] = v[1].x, s[4] = v[1].y, s[5] = v[1].z;
        s[6] = v[0].x, s[7] = v[0].y, s[8] = v[0].z;
        s[9] = v[1].x, s[10] = v[1].y, s[11] = v[1].z;
        s[12] = v[3].x, s[13] = v[3].y, s[14] = v[3].z;
        s[15] = v[2].x, s[16] = v[2].y, s[17] = v[2].z;
    }
    
    glGenVertexArrays (1, &baseaoID);
    glBindVertexArray (baseaoID);
    glGenBuffers (1, &baseboID);
    glBindBuffer (GL_ARRAY_BUFFER, baseboID);
    glBufferData (GL_ARRAY_BUFFER, slice*9*sizeof (GLfloat*), base, GL_STATIC_DRAW);
    
    glGenVertexArrays (1, &coveraoID);
    glBindVertexArray (coveraoID);
    glGenBuffers (1, &coverboID);
    glBindBuffer (GL_ARRAY_BUFFER, coverboID);
    glBufferData (GL_ARRAY_BUFFER, slice*9*sizeof (GLfloat*), cover, GL_STATIC_DRAW);
    
    glGenVertexArrays (1, &sideaoID);
    glBindVertexArray (sideaoID);
    glGenBuffers (1, &sideboID);
    glBindBuffer (GL_ARRAY_BUFFER, sideboID);
    glBufferData (GL_ARRAY_BUFFER, slice*18*sizeof (GLfloat*), side, GL_STATIC_DRAW);
    
    baseColor = new GLfloat[slice*9];
    coverColor = new GLfloat[slice*9];
    sideColor = new GLfloat[slice*18];
    
    for (int i = 0; i < slice*9; i++)
        baseColor[i] = 0.0;
    for (int i = 0; i < slice*9; i++)
        coverColor[i] = 0.0;
    for (int i = 0; i < slice*18; i++)
        sideColor[i] = 0.0;
    
    glGenBuffers (1, &basecboID);
    glBindBuffer (GL_ARRAY_BUFFER, basecboID);
    glBufferData (GL_ARRAY_BUFFER, slice*9*sizeof (GLfloat*), baseColor, GL_STATIC_DRAW);
    
    glGenBuffers (1, &covercboID);
    glBindBuffer (GL_ARRAY_BUFFER, covercboID);
    glBufferData (GL_ARRAY_BUFFER, slice*9*sizeof (GLfloat*), coverColor, GL_STATIC_DRAW);
    
    glGenBuffers (1, &sidecboID);
    glBindBuffer (GL_ARRAY_BUFFER, sidecboID);
    glBufferData (GL_ARRAY_BUFFER, slice*18*sizeof (GLfloat*), sideColor, GL_STATIC_DRAW);
    
    if (shuffleColor) {
        setBaseColor (Color (true));
        setCoverColor (Color (true));
        setSideColor (Color (true));
    }
}

void Prism::render () {
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, baseboID);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, basecboID);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    glDrawArrays (GL_TRIANGLES, 0, slice*3);
    glDisableVertexAttribArray (0);
    glDisableVertexAttribArray (1);
    
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, coverboID);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, covercboID);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    glDrawArrays (GL_TRIANGLES, 0, slice*3);
    glDisableVertexAttribArray (0);
    glDisableVertexAttribArray (1);
    
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, sideboID);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, sidecboID);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    glDrawArrays (GL_TRIANGLES, 0, slice*6);
    glDisableVertexAttribArray (0);
    glDisableVertexAttribArray (1);
}

void Prism::clean () {
    glDeleteVertexArrays (1, &baseaoID);
    glDeleteBuffers (1, &baseboID);
    glDeleteBuffers (1, &basecboID);
    
    glDeleteVertexArrays (1, &coveraoID);
    glDeleteBuffers (1, &coverboID);
    glDeleteBuffers (1, &covercboID);
    
    glDeleteVertexArrays (1, &sideaoID);
    glDeleteBuffers (1, &sideboID);
    glDeleteBuffers (1, &sidecboID);
}

Prism *Prism::setBaseColor (int slice, Color color) {
    if (slice < this->slice) {
        for (int i = 0; i < 3; i++)
            baseColor[slice*9+i*3+0] = color.r,
            baseColor[slice*9+i*3+1] = color.g,
            baseColor[slice*9+i*3+2] = color.b;
        glBindBuffer (GL_ARRAY_BUFFER, basecboID);
        glBufferData (GL_ARRAY_BUFFER, this->slice*9*4, baseColor, GL_STATIC_DRAW);
    }
    return this;
}

Prism *Prism::setBaseColor (Color color) {
    for (int i = 0; i < slice; i++)
        setBaseColor (i, color);
    return this;
}

Prism *Prism::setCoverColor (int slice, Color color) {
    if (slice < this->slice)
        for (int i = 0; i < 3; i++)
            coverColor[slice*9+i*3+0] = color.r,
            coverColor[slice*9+i*3+1] = color.g,
            coverColor[slice*9+i*3+2] = color.b;
    glBindBuffer (GL_ARRAY_BUFFER, covercboID);
    glBufferData (GL_ARRAY_BUFFER, this->slice*9*4, coverColor, GL_STATIC_DRAW);
    return this;
}

Prism *Prism::setCoverColor (Color color) {
    for (int i = 0; i < slice; i++)
        setCoverColor (i, color);
    return this;
}

Prism *Prism::setSideColor (int slice, Color color) {
    if (0 <= slice && slice < this->slice) {
        for (int i = 0; i < 6; i++)
            sideColor[slice*18+i*3+0] = color.r,
            sideColor[slice*18+i*3+1] = color.g,
            sideColor[slice*18+i*3+2] = color.b;
        glBindBuffer (GL_ARRAY_BUFFER, sidecboID);
        glBufferData (GL_ARRAY_BUFFER, this->slice*18*4, sideColor, GL_STATIC_DRAW);
    }
    return this;
}

Prism *Prism::setSideColor (Color color) {
    for (int i = 0; i < slice; i++)
        setSideColor (i, color);
    return this;
}

Prism *Prism::setColor (int slice, Color color) {
    setBaseColor (slice, color);
    setCoverColor (slice, color);
    setSideColor (slice, color);
    return this;
}

Prism *Prism::setRainbowColor () {
    for (int i = 0; i < slice; i++)
        setBaseColor (i, Color (true)),
        setCoverColor (i, Color (true)),
        setSideColor (i, Color (true));
    return this;
}

void Prism::move (int axis, GLfloat amount) {
    for (int i = 0; i < slice*9; i+=3)
        cover[i+axis] += amount,
        base[i+axis] += amount,
        side[i+axis] += amount,
        side[slice*9+i+axis] += amount;
    glBindBuffer (GL_ARRAY_BUFFER, coverboID);
    glBufferData (GL_ARRAY_BUFFER, slice*9*4, cover, GL_STATIC_DRAW);
    glBindBuffer (GL_ARRAY_BUFFER, baseboID);
    glBufferData (GL_ARRAY_BUFFER, slice*9*4, base, GL_STATIC_DRAW);
    glBindBuffer (GL_ARRAY_BUFFER, baseboID);
    glBufferData (GL_ARRAY_BUFFER, slice*18*4, side, GL_STATIC_DRAW);
}

void Prism::rotate (GLfloat x, GLfloat y, GLfloat z) {

}

void Prism::scale (GLfloat x, GLfloat y, GLfloat z) {

}
