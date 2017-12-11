#include <cmath>
#include "Prism.hpp"

using namespace glm;

Prism::Prism ()
: Prism (0, 0, 0, 5, 2, 4) {}

Prism::Prism (float x, float y, float z, int n, float size, float height)
: Prism (x, y, z, n, size, size, height) {}

// maximum size between base and cover to calculate margin size
#define maxSize std::max (baseSize, coverSize)
Prism::Prism (float x, float y, float z, int n, float baseSize, float coverSize, float height) {
    if (n > 360) n = 360;
    slice = n;
    
    TRIANGLE_COUNT = 4 * 3 * slice;
    BUFFER_LENGTH = TRIANGLE_COUNT * 3;
    BUFFER_SIZE = BUFFER_LENGTH * sizeof (float*);
    
    buffer = new float[BUFFER_LENGTH];
    cover = &buffer[0];
    base = &buffer[9*slice];
    side = &buffer[18*slice];
    
    float y1, y2;
    y1 = y;
    y2 = y + height;
    
    for (int i = 0; i < slice; i++) {
        double a1, a2;
        a1 = i * (2 * M_PI / slice);
        a2 = ((i+1) % slice) * (2 * M_PI / slice);
        
        double x1, x2, x3, x4, z1, z2, z3, z4;
        x1 = x + baseSize * cos (a1);
        z1 = z + baseSize * sin (a1);
        x2 = x + baseSize * cos (a2);
        z2 = z + baseSize * sin (a2);
        x3 = x + coverSize * cos (a1);
        z3 = z + coverSize * sin (a1);
        x4 = x + coverSize * cos (a2);
        z4 = z + coverSize * sin (a2);
        
        // 32
        // 01
        vec3 v[4];
        v[0] = vec3 (x1, y1, z1);
        v[1] = vec3 (x2, y1, z2);
        v[2] = vec3 (x4, y2, z4);
        v[3] = vec3 (x3, y2, z3);
        
        float *s;
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
    
    init ();
    
    coverColor = &colors[0];
    baseColor = &colors[9*slice];
    sideColor = &colors[18*slice];
    
    setBaseColor (Color ());
    setCoverColor (Color ());
    setSideColor (Color ());
}

void Prism::setCoverColor (int slice, Color color) {
    if (slice < 0 || slice >= this->slice)
        return;
    
    slice *= 9;
    for (int i = 0; i < 9; i += 3)
        for (int j = 0; j < 3; j++)
            coverColor[slice+i+j] = color[j];
    updateBuffer ();
}

void Prism::setCoverColor (Color color) {
    for (int i = 0; i < slice; i++)
        setCoverColor (i, color);
}

void Prism::setBaseColor (int slice, Color color) {
    if (slice < 0 || slice >= this->slice)
        return;
    
    slice *= 9;
    for (int i = 0; i < 9; i += 3)
        for (int j = 0; j < 3; j++)
            baseColor[slice+i+j] = color[j];
    updateBuffer ();
}

void Prism::setBaseColor (Color color) {
    for (int i = 0; i < slice; i++)
        setBaseColor (i, color);
}

void Prism::setSideColor (int slice, Color color) {
    if (slice < 0 || slice >= this->slice)
        return;
    
    slice *= 18;
    for (int i = 0; i < 18; i += 3)
        for (int j = 0; j < 3; j++)
            sideColor[slice+i+j] = color[j];
    updateBuffer ();
}

void Prism::setSideColor (Color color) {
    for (int i = 0; i < slice; i++)
        setSideColor (i, color);
}

void Prism::setColor (int slice, Color color) {
    setBaseColor (slice, color);
    setCoverColor (slice, color);
    setSideColor (slice, color);
}

void Prism::setColor (Color color) {
    setCoverColor (color);
    setBaseColor (color);
    setSideColor (color);
}

void Prism::setRainbowColor () {
    for (int i = 0; i < slice; i++) {
        setBaseColor (i, Color ());
        setCoverColor (i, Color ());
        setSideColor (i, Color ());
    }
}
