#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <common/controls.hpp>
#include <common/shader.hpp>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <cmath>

typedef struct _coord {
    GLfloat x, y, z;
    
    _coord () {
        x = y = z = 0;
    }
    
    _coord (GLfloat x, GLfloat y, GLfloat z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    void set (GLfloat x, GLfloat y, GLfloat z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
} Coord;


typedef struct _color {
    GLfloat r, g, b;
    
    _color (GLfloat r, GLfloat g, GLfloat b, bool hex) {
        if (hex) {
            this->r = r / 255;
            this->g = g / 255;
            this->b = b / 255;
        }
        else {
            this->r = r;
            this->g = g;
            this->b = b;
        }
    }
    
    _color () {
        r = (GLfloat) rand() / (GLfloat) RAND_MAX;
        g = (GLfloat) rand() / (GLfloat) RAND_MAX;
        b = (GLfloat) rand() / (GLfloat) RAND_MAX;
    }
    
    void set (GLfloat r, GLfloat g, GLfloat b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
} Color;


class Object {
public:
    virtual void render () = 0;
    virtual void clean () = 0;
    virtual void move (int coord, GLfloat amount) = 0;
    static const int X=0, Y=1, Z=2;
};


class Box : public Object {
public:
    Box () : Box (-1, 1, -1, 1, -1, 1) {}
    
    Box (GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2, bool shuffleColor = false) {
        // As we already knew in elementary school, a box has 8 vertices.
        // These vertices will be used to build buffer for the box
        // which use the same 8 vertices multiple times.
        Coord v[8];
        v[0].set (x1, y1, z2);
        v[1].set (x2, y1, z2);
        v[2].set (x2, y1, z1);
        v[3].set (x1, y1, z1);
        v[4].set (x1, y2, z2);
        v[5].set (x2, y2, z2);
        v[6].set (x2, y2, z1);
        v[7].set (x1, y2, z1);
        
        buffer = new GLfloat[108] {
            // left
            v[3].x, v[3].y, v[3].z,
            v[0].x, v[0].y, v[0].z,
            v[4].x, v[4].y, v[4].z,
            v[3].x, v[3].y, v[3].z,
            v[4].x, v[4].y, v[4].z,
            v[7].x, v[7].y, v[7].z,
            
            // top
            v[4].x, v[4].y, v[4].z,
            v[5].x, v[5].y, v[5].z,
            v[7].x, v[7].y, v[7].z,
            v[7].x, v[7].y, v[7].z,
            v[5].x, v[5].y, v[5].z,
            v[6].x, v[6].y, v[6].z,
            
            // front
            v[0].x, v[0].y, v[0].z,
            v[1].x, v[1].y, v[1].z,
            v[4].x, v[4].y, v[4].z,
            v[5].x, v[5].y, v[5].z,
            v[4].x, v[4].y, v[4].z,
            v[1].x, v[1].y, v[1].z,
            
            // right
            v[1].x, v[1].y, v[1].z,
            v[2].x, v[2].y, v[2].z,
            v[5].x, v[5].y, v[5].z,
            v[6].x, v[6].y, v[6].z,
            v[5].x, v[5].y, v[5].z,
            v[2].x, v[2].y, v[2].z,
            
            // bottom
            v[1].x, v[1].y, v[1].z,
            v[0].x, v[0].y, v[0].z,
            v[3].x, v[3].y, v[3].z,
            v[1].x, v[1].y, v[1].z,
            v[3].x, v[3].y, v[3].z,
            v[2].x, v[2].y, v[2].z,
            
            // rear
            v[6].x, v[6].y, v[6].z,
            v[3].x, v[3].y, v[3].z,
            v[7].x, v[7].y, v[7].z,
            v[6].x, v[6].y, v[6].z,
            v[2].x, v[2].y, v[2].z,
            v[3].x, v[3].y, v[3].z,
        };
        
        glGenVertexArrays (1, &vaoID);
        glBindVertexArray (vaoID);
        glGenBuffers (1, &vboID);
        glBindBuffer (GL_ARRAY_BUFFER, vboID);
        glBufferData (GL_ARRAY_BUFFER, 108*4, buffer, GL_STATIC_DRAW);
        
        // Initial color for all faces of the box is black.
        // It can be overridden by calling @setFaceColor method.
        colors = new GLfloat[108];
        for (int i = 0; i < 108; i++)
            colors[i] = 0.0f;
    
        // if size parameter of glBufferData didn't use sizeof (),
        // it has to be length of color array multiplied by 4.
        // Still figuring out what this number (4) means. \:
        glGenBuffers (1, &cboID);
        glBindBuffer (GL_ARRAY_BUFFER, cboID);
        glBufferData (GL_ARRAY_BUFFER, 108*4, colors, GL_STATIC_DRAW);
        
        if (shuffleColor)
            for (int i = 0; i < 6; i++)
                setFaceColor (i, Color ());
    }
    
    void render () override {
        glEnableVertexAttribArray (0);
        glBindBuffer (GL_ARRAY_BUFFER, vboID);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);
        
        glEnableVertexAttribArray (1);
        glBindBuffer (GL_ARRAY_BUFFER, cboID);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);
        
        // 6 faces, each 2 triangles with 3 vertex
        glDrawArrays (GL_TRIANGLES, 0, 6*2*3);
        
        glDisableVertexAttribArray (0);
        glDisableVertexAttribArray (1);
    }
    
    void clean () override {
        glDeleteVertexArrays (1, &vaoID);
        glDeleteBuffers (1, &vboID);
        glDeleteBuffers (1, &cboID);
    }
    
    void move (int coord, GLfloat amount) override {
        for (int i = 0; i < 108; i+=3)
            buffer[i+coord] += amount;
        glBindBuffer (GL_ARRAY_BUFFER, vboID);
        glBufferData (GL_ARRAY_BUFFER, 108*4, buffer, GL_STATIC_DRAW);
    }
    
    // Constants to represents each faces of the box.
    // The order of enum must follow vertex array
    // draw order.
    static const int LEFT=0, TOP=1, FRONT=2, RIGHT=3, BOTTOM=4, REAR=5;
    
    Box *setFaceColor (int face, Color color) {
        for (int i = 0; i < 6; i++)
            colors[18*face+3*i+0] = color.r,
            colors[18*face+3*i+1] = color.g,
            colors[18*face+3*i+2] = color.b;
        glBindBuffer (GL_ARRAY_BUFFER, cboID);
        glBufferData (GL_ARRAY_BUFFER, 108*4, colors, GL_STATIC_DRAW);
        return this;
    }
    
    Box *setFaceColor (Color color) {
        for (int i = 0; i < 6; i++)
            setFaceColor (i, color);
        return this;
    }

protected:
    // colors array need to be defined as class attribute
    // so that it can be changed after initialization.
    GLfloat *buffer {};
    GLfloat *colors {};
    GLuint vaoID {}, vboID {}, cboID {};
};


class Plane : public Box {
public:
    Plane () : Plane (0, 0, 0, 20) {}
    
    Plane (GLfloat x, GLfloat y, GLfloat z, GLfloat size, Color color)
    : Box (x-(size/2), x+(size/2), y-0.1f, y, z-(size/2), z+(size/2)) {
        setFaceColor (TOP, color);
    }
    
    Plane (GLfloat x, GLfloat y, GLfloat z, GLfloat size)
    : Plane (x, y, z, size, Color (109, 88, 74, true)) {}
};


class Cube : public Box {
public:
    Cube () : Cube (0, 0, 0, 2) {}
    
    Cube (GLfloat x, GLfloat y, GLfloat z, GLfloat size, bool shuffleColor = false)
    : Box (x-(size/2), x+(size/2), y, y+size, z-(size/2), z+(size/2), shuffleColor) {}
};


class Prism : public Object {
public:
    Prism () : Prism (0, 0, 0, 5, 2, 4) {}
    
    Prism (GLfloat x, GLfloat y, GLfloat z, int n, GLfloat size, GLfloat height, bool shuffleColor = false)
    : Prism (x, y, z, n, size, size, height, shuffleColor) {}
    
    void render () override {
        glEnableVertexAttribArray (0);
        glBindBuffer (GL_ARRAY_BUFFER, baseboID);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);
        glEnableVertexAttribArray (1);
        glBindBuffer (GL_ARRAY_BUFFER, basecboID);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);
        glDrawArrays (GL_TRIANGLES, 0, slice*3);
        glDisableVertexAttribArray (0);
        glDisableVertexAttribArray (1);
        
        glEnableVertexAttribArray (0);
        glBindBuffer (GL_ARRAY_BUFFER, coverboID);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);
        glEnableVertexAttribArray (1);
        glBindBuffer (GL_ARRAY_BUFFER, covercboID);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);
        glDrawArrays (GL_TRIANGLES, 0, slice*3);
        glDisableVertexAttribArray (0);
        glDisableVertexAttribArray (1);
        
        glEnableVertexAttribArray (0);
        glBindBuffer (GL_ARRAY_BUFFER, sideboID);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);
        glEnableVertexAttribArray (1);
        glBindBuffer (GL_ARRAY_BUFFER, sidecboID);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);
        glDrawArrays (GL_TRIANGLES, 0, slice*6);
        glDisableVertexAttribArray (0);
        glDisableVertexAttribArray (1);
    }
    
    void clean () override {
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
    
    void move (int coord, GLfloat amount) override {
        for (int i = 0; i < slice*9; i+=3)
            base[i+coord] += amount, cover[i+coord] += amount,
            side[i+coord] += amount, side[slice*9+i+coord] += amount;
        glBindBuffer (GL_ARRAY_BUFFER, baseboID);
        glBufferData (GL_ARRAY_BUFFER, slice*9*4, base, GL_STATIC_DRAW);
        glBindBuffer (GL_ARRAY_BUFFER, coverboID);
        glBufferData (GL_ARRAY_BUFFER, slice*9*4, cover, GL_STATIC_DRAW);
        glBindBuffer (GL_ARRAY_BUFFER, baseboID);
        glBufferData (GL_ARRAY_BUFFER, slice*18*4, side, GL_STATIC_DRAW);
    }
    
    Prism *setBaseColor (int slice, Color color) {
        if (slice < this->slice)
            for (int i = 0; i < 3; i++)
                baseColor[slice*9+i*3+0] = color.r,
                baseColor[slice*9+i*3+1] = color.g,
                baseColor[slice*9+i*3+2] = color.b;
        glBindBuffer (GL_ARRAY_BUFFER, basecboID);
        glBufferData (GL_ARRAY_BUFFER, this->slice*9*4, baseColor, GL_STATIC_DRAW);
        return this;
    }
    
    Prism *setBaseColor (Color color) {
        for (int i = 0; i < slice; i++)
            setBaseColor (i, color);
        return this;
    }
    
    Prism *setCoverColor (int slice, Color color) {
        if (slice < this->slice)
            for (int i = 0; i < 3; i++)
                coverColor[slice*9+i*3+0] = color.r,
                coverColor[slice*9+i*3+1] = color.g,
                coverColor[slice*9+i*3+2] = color.b;
        glBindBuffer (GL_ARRAY_BUFFER, covercboID);
        glBufferData (GL_ARRAY_BUFFER, this->slice*9*4, coverColor, GL_STATIC_DRAW);
        return this;
    }
    
    Prism *setCoverColor (Color color) {
        for (int i = 0; i < slice; i++)
            setCoverColor (i, color);
        return this;
    }
    
    Prism *setSideColor (int slice, Color color) {
        if (slice < this->slice) {
            for (int i = 0; i < 6; i++)
                sideColor[slice*18+i*3+0] = color.r,
                sideColor[slice*18+i*3+1] = color.g,
                sideColor[slice*18+i*3+2] = color.b;
            glBindBuffer (GL_ARRAY_BUFFER, sidecboID);
            glBufferData (GL_ARRAY_BUFFER, this->slice*18*4, sideColor, GL_STATIC_DRAW);
        }
        return this;
    }
    
    Prism *setSideColor (Color color) {
        for (int i = 0; i < slice; i++)
            setSideColor (i, color);
        return this;
    }
    
    Prism *setColor (int slice, Color color) {
        setBaseColor (slice, color);
        setCoverColor (slice, color);
        setSideColor (slice, color);
        return this;
    }
    
    Prism *setRainbowColor () {
        for (int i = 0; i < slice; i++)
            setBaseColor (i, Color ())->setCoverColor (i, Color ())->setSideColor (i, Color ());
        return this;
    }
    
    Prism *setColor (Color color) {
        for (int i = 0; i < slice; i++)
            setColor (i, color);
        return this;
    }
    
protected:
    Prism (GLfloat x, GLfloat y, GLfloat z, int n, GLfloat baseSize, GLfloat coverSize, GLfloat height, bool shuffleColor = false) {
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
        glBufferData (GL_ARRAY_BUFFER, slice*9*4, base, GL_STATIC_DRAW);
        
        glGenVertexArrays (1, &coveraoID);
        glBindVertexArray (coveraoID);
        glGenBuffers (1, &coverboID);
        glBindBuffer (GL_ARRAY_BUFFER, coverboID);
        glBufferData (GL_ARRAY_BUFFER, slice*9*4, cover, GL_STATIC_DRAW);
        
        glGenVertexArrays (1, &sideaoID);
        glBindVertexArray (sideaoID);
        glGenBuffers (1, &sideboID);
        glBindBuffer (GL_ARRAY_BUFFER, sideboID);
        glBufferData (GL_ARRAY_BUFFER, slice*18*4, side, GL_STATIC_DRAW);
        
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
        glBufferData (GL_ARRAY_BUFFER, slice*9*4, baseColor, GL_STATIC_DRAW);
        
        glGenBuffers (1, &covercboID);
        glBindBuffer (GL_ARRAY_BUFFER, covercboID);
        glBufferData (GL_ARRAY_BUFFER, slice*9*4, coverColor, GL_STATIC_DRAW);
        
        glGenBuffers (1, &sidecboID);
        glBindBuffer (GL_ARRAY_BUFFER, sidecboID);
        glBufferData (GL_ARRAY_BUFFER, slice*18*4, sideColor, GL_STATIC_DRAW);
        
        if (shuffleColor) {
            setBaseColor (Color ());
            setCoverColor (Color ());
            setSideColor (Color ());
        }
    }
    
private:
    GLuint baseaoID {}, baseboID {}, basecboID {},
           coveraoID {}, coverboID {}, covercboID {},
           sideaoID {}, sideboID {}, sidecboID {};
    
    GLfloat *side, *base, *cover;
    GLfloat *baseColor, *coverColor, *sideColor;
    int slice;
};


// Cylinder is a prism with a lot of slice (n)
class Cylinder : public Prism {
public:
    Cylinder () : Cylinder (0, 0, 0, 2, 4) {}
    
    Cylinder (GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height, bool shuffleColor = false)
    : Prism (x, y, z, 360, r, height, shuffleColor) {}
};


// Pyramid is a prism with cover size of 0
class Pyramid : public Prism {
public:
    Pyramid () : Pyramid (0, 0, 0, 4, 2, 3) {}
    
    Pyramid (GLfloat x, GLfloat y, GLfloat z, int n, GLfloat size, GLfloat height, bool shuffleColor = false)
    : Prism (x, y, z, n, size, 0.0, height, shuffleColor) {}
};


// Cone is a pyramid with a lot of n
class Cone : public Pyramid {
public:
    Cone () : Cone (0, 0, 0, 2, 4) {}
    
    Cone (GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height, bool shuffleColor = false)
    : Pyramid (x, y, z, 360, r, height, shuffleColor) {}
};
