#include <algorithm>
#include <cmath>
#include <GL/glew.h>
#include <cstdio>
#include <glm/vec3.hpp>
#include "Prism.hpp"

using namespace glm;

Prism::Prism ()
: Prism (0, 0, 0, 5, 2, 4, true) {}

Prism::Prism (GLfloat x, GLfloat y, GLfloat z, int n, GLfloat size, GLfloat height, bool shuffleColor)
: Prism (x, y, z, n, size, size, height, shuffleColor) {}

// maximum size between base and cover to calculate margin size
#define maxSize std::max (baseSize, coverSize)
Prism::Prism (GLfloat x, GLfloat y, GLfloat z, int n, GLfloat baseSize, GLfloat coverSize, GLfloat height, bool shuffleColor)
: Object (x-maxSize, x+maxSize, y, y+height, z-maxSize, z+maxSize) {
    if (n > 360) n = 360;
    slice = n;
    EDGE_LENGTH = 9 * slice;
    EDGE_SIZE = EDGE_LENGTH * sizeof (GLfloat);
    SIDE_LENGTH = 18 * slice;
    SIDE_SIZE = SIDE_LENGTH * sizeof (GLfloat);
    
    cover = new GLfloat[EDGE_LENGTH];
    base = new GLfloat[EDGE_LENGTH];
    side = new GLfloat[SIDE_LENGTH];
    
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
        vec3 v[4];
        v[0] = vec3 (x1, y1, z1);
        v[1] = vec3 (x2, y1, z2);
        v[2] = vec3 (x4, y2, z4);
        v[3] = vec3 (x3, y2, z3);
        
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
    
    glGenVertexArrays (1, &coveraoID);
    glBindVertexArray (coveraoID);
    glGenBuffers (1, &coverboID);
    glBindBuffer (GL_ARRAY_BUFFER, coverboID);
    glBufferData (GL_ARRAY_BUFFER, EDGE_SIZE, cover, GL_STATIC_DRAW);
    
    glGenVertexArrays (1, &baseaoID);
    glBindVertexArray (baseaoID);
    glGenBuffers (1, &baseboID);
    glBindBuffer (GL_ARRAY_BUFFER, baseboID);
    glBufferData (GL_ARRAY_BUFFER, EDGE_SIZE, base, GL_STATIC_DRAW);
    
    glGenVertexArrays (1, &sideaoID);
    glBindVertexArray (sideaoID);
    glGenBuffers (1, &sideboID);
    glBindBuffer (GL_ARRAY_BUFFER, sideboID);
    glBufferData (GL_ARRAY_BUFFER, SIDE_SIZE, side, GL_STATIC_DRAW);
    
    coverColor = new GLfloat[EDGE_LENGTH];
    baseColor = new GLfloat[EDGE_LENGTH];
    sideColor = new GLfloat[SIDE_LENGTH];
    
    for (int i = 0; i < EDGE_LENGTH; i++)
        baseColor[i] = 0.0;
    for (int i = 0; i < EDGE_LENGTH; i++)
        coverColor[i] = 0.0;
    for (int i = 0; i < SIDE_LENGTH; i++)
        sideColor[i] = 0.0;
    
    glGenBuffers (1, &covercboID);
    glBindBuffer (GL_ARRAY_BUFFER, covercboID);
    glBufferData (GL_ARRAY_BUFFER, EDGE_SIZE, coverColor, GL_STATIC_DRAW);
    
    glGenBuffers (1, &basecboID);
    glBindBuffer (GL_ARRAY_BUFFER, basecboID);
    glBufferData (GL_ARRAY_BUFFER, EDGE_SIZE, baseColor, GL_STATIC_DRAW);
    
    glGenBuffers (1, &sidecboID);
    glBindBuffer (GL_ARRAY_BUFFER, sidecboID);
    glBufferData (GL_ARRAY_BUFFER, SIDE_SIZE, sideColor, GL_STATIC_DRAW);
    
    if (shuffleColor) {
        setBaseColor (Color (true));
        setCoverColor (Color (true));
        setSideColor (Color (true));
    }
    
    _measure ();
}

void Prism::render () {
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
    glBindBuffer (GL_ARRAY_BUFFER, baseboID);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, basecboID);
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
    glDeleteVertexArrays (1, &coveraoID);
    glDeleteBuffers (1, &coverboID);
    glDeleteBuffers (1, &covercboID);
    
    glDeleteVertexArrays (1, &baseaoID);
    glDeleteBuffers (1, &baseboID);
    glDeleteBuffers (1, &basecboID);
    
    glDeleteVertexArrays (1, &sideaoID);
    glDeleteBuffers (1, &sideboID);
    glDeleteBuffers (1, &sidecboID);
}

Prism *Prism::setCoverColor (int slice, Color color) {
    if (slice < this->slice)
        for (int i = 0; i < 3; i++)
            coverColor[slice*9+i*3+0] = color.r,
            coverColor[slice*9+i*3+1] = color.g,
            coverColor[slice*9+i*3+2] = color.b;
    glBindBuffer (GL_ARRAY_BUFFER, covercboID);
    glBufferData (GL_ARRAY_BUFFER, EDGE_SIZE, coverColor, GL_STATIC_DRAW);
    return this;
}

Prism *Prism::setCoverColor (Color color) {
    for (int i = 0; i < slice; i++)
        setCoverColor (i, color);
    return this;
}

Prism *Prism::setBaseColor (int slice, Color color) {
    if (slice < this->slice) {
        for (int i = 0; i < 3; i++)
            baseColor[slice*9+i*3+0] = color.r,
            baseColor[slice*9+i*3+1] = color.g,
            baseColor[slice*9+i*3+2] = color.b;
        glBindBuffer (GL_ARRAY_BUFFER, basecboID);
        glBufferData (GL_ARRAY_BUFFER, EDGE_SIZE, baseColor, GL_STATIC_DRAW);
    }
    return this;
}

Prism *Prism::setBaseColor (Color color) {
    for (int i = 0; i < slice; i++)
        setBaseColor (i, color);
    return this;
}

Prism *Prism::setSideColor (int slice, Color color) {
    if (0 <= slice && slice < this->slice) {
        for (int i = 0; i < 6; i++)
            sideColor[slice*18+i*3+0] = color.r,
            sideColor[slice*18+i*3+1] = color.g,
            sideColor[slice*18+i*3+2] = color.b;
        glBindBuffer (GL_ARRAY_BUFFER, sidecboID);
        glBufferData (GL_ARRAY_BUFFER, SIDE_SIZE, sideColor, GL_STATIC_DRAW);
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

void trans (mat4 T, GLfloat vect[]) {
    vec4 res, v;
    v[3] = 1;
    for (int i = 0; i < 3; i++)
        v[i] = vect[i];
    res = v * T;
    for (int i = 0; i < 3; i++)
        vect[i] = res[i];
}

void Prism::transform (mat4 T, int type) {
    GLfloat copy[EDGE_LENGTH];
    for (int i = 0; i < EDGE_LENGTH; i++)
        copy[i] = cover[i];
    
    for (int i = 0; i < 9*slice; i += 3) {
        trans (T, &cover[i]);
        trans (T, &base[i]);
        trans (T, &side[i]);
        trans (T, &side[9*slice+i]);
    }
    
    glBindBuffer (GL_ARRAY_BUFFER, coverboID);
    glBufferData (GL_ARRAY_BUFFER, EDGE_SIZE, cover, GL_STATIC_DRAW);
    glBindBuffer (GL_ARRAY_BUFFER, baseboID);
    glBufferData (GL_ARRAY_BUFFER, EDGE_SIZE, base, GL_STATIC_DRAW);
    glBindBuffer (GL_ARRAY_BUFFER, sideboID);
    glBufferData (GL_ARRAY_BUFFER, SIDE_SIZE, side, GL_STATIC_DRAW);
}

void Prism::measure () {
    using std::min;
    using std::max;
    #define min5(a, b, c, d, e) min (a, min (b, min (c, min (d, e))))
    #define max5(a, b, c, d, e) max (a, max (b, max (c, max (d, e))))
    
    for (int i = 0; i < 9*slice; i += 3) {
        for (int j = 0; j < 3; j++) {
            margin[j][0] = min5 (margin[j][0], cover[i+j], base[i+j], side[i+j], side[9*slice+i+j]);
            margin[j][1] = max5 (margin[j][1], cover[i+j], base[i+j], side[i+j], side[9*slice+i+j]);
        }
    }
}
