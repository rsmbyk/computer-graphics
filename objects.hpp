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

typedef struct coord {
    GLfloat x, y, z;
    
    void set (GLfloat x, GLfloat y, GLfloat z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
} Coord;

class Object {
public:
    virtual void render () = 0;
    GLuint vaoID {}, vboID {}, cboID {};
    GLfloat *colors;
    Coord *v;
    
    virtual void clean () {
        glDeleteVertexArrays (1, &vaoID);
        glDeleteBuffers (1, &vboID);
    }
};

class Box : public Object {
public:
    Box (float x1, float x2, float y1, float y2, float z1, float z2) {
        Coord v[8];
        v[0].set (x1, y1, z2);
        v[1].set (x2, y1, z2);
        v[2].set (x2, y1, z1);
        v[3].set (x1, y1, z1);
        v[4].set (x1, y2, z2);
        v[5].set (x2, y2, z2);
        v[6].set (x2, y2, z1);
        v[7].set (x1, y2, z1);
        
        GLfloat buffer[108] = {
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
        glBufferData (GL_ARRAY_BUFFER, sizeof (buffer), buffer, GL_STATIC_DRAW);
        
        for (int i = 0; i < 108; i++)
            colors[i] = 0.0f;
        
        glGenBuffers (1, &cboID);
        glBindBuffer (GL_ARRAY_BUFFER, cboID);
        glBufferData (GL_ARRAY_BUFFER, sizeof (colors), colors, GL_STATIC_DRAW);
    }
    
    void render () override {
        glEnableVertexAttribArray (0);
        glBindBuffer (GL_ARRAY_BUFFER, vboID);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        
        glEnableVertexAttribArray (1);
        glBindBuffer (GL_ARRAY_BUFFER, cboID);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        
        glDrawArrays (GL_TRIANGLES, 0, 36);
        
        glDisableVertexAttribArray (0);
        glDisableVertexAttribArray (1);
    }
    
    virtual void clean () override {
        Object::clean ();
        glDeleteVertexArrays (1, &cboID);
        glDeleteBuffers (1, &cboID);
    }

//protected:
    static const int LEFT=0, TOP=1, FRONT=2, RIGHT=3, BOTTOM=4, REAR=5;
    GLfloat colors[108];
    
    void setSideColor (int side, float r, float g, float b) {
        for (int i = 0; i < 6; i++)
            colors[18*side+3*i+0] = r,
            colors[18*side+3*i+1] = g,
            colors[18*side+3*i+2] = b;
        glBufferData (GL_ARRAY_BUFFER, sizeof (colors), colors, GL_STATIC_DRAW);
    }
};

class Plane : public Box {
public:
    Plane (float x, float y, float z, float size) : Box (x-(size/2), x+(size/2), y, y+0.1f, z-(size/2), z+(size/2)) {
        setSideColor (TOP, 0.50, 0.30, 0.0);
    }
};

class Cube : public Box {
public:
    Cube (float x, float y, float z, float size) : Box (x-(size/2), x+(size/2), y, y+size, z-(size/2), z+(size/2)) {
        GLfloat x1, x2, y1, y2, z1, z2;
        x1 = x - (size / 2);
        x2 = x + (size / 2);
        y1 = y;
        y2 = y + size;
        z1 = z - (size / 2);
        z2 = z + (size / 2);
        setSideColor (LEFT, 0.25f, 0.0f, 0.0f);
        setSideColor (RIGHT, 0.25f, 0.0f, 0.0f);
        setSideColor (FRONT, 0.0f, 0.75f, 0.0f);
        setSideColor (REAR, 0.0f, 0.75f, 0.0f);
        setSideColor (TOP, 0.0f, 0.0f, 0.5f);
        setSideColor (BOTTOM, 0.0f, 0.0f, 0.5f);
    }
};

class Cylinder : public Object {
public:
    Cylinder (float x, float y, float z, float r, float height, int slice) {
        this->slice = slice;
        GLfloat side[slice*18], base[slice*9], cover[slice*9];
        float y1, y2;
        y1 = y;
        y2 = y + height;
        
        for (int i = 0; i < slice; i++) {
            double a1, a2;
            a1 = i * (2 * M_PI / slice);
            a2 = ((i+1) % slice) * (2 * M_PI / slice);
            
            float x1, x2, z1, z2;
            x1 = x + r * cos (a1);
            z1 = z + r * sin (a1);
            x2 = x + r * cos (a2);
            z2 = z + r * sin (a2);
            
            GLfloat *s = &side[i*18];
            s[0] = x1, s[1] = y2, s[2] = z1;
            s[3] = x2, s[4] = y1, s[5] = z2;
            s[6] = x1, s[7] = y1, s[8] = z1;
            s[9] = x2, s[10] = y1, s[11] = z2;
            s[12] = x1, s[13] = y2, s[14] = z1;
            s[15] = x2, s[16] = y2, s[17] = z2;
            
            s = &base[i*9];
            s[0] = x, s[1] = y1, s[2] = z;
            s[3] = x2, s[4] = y1, s[5] = z2;
            s[6] = x1, s[7] = y1, s[8] = z1;
            
            s = &cover[i*9];
            s[0] = x, s[1] = y2, s[2] = z;
            s[3] = x2, s[4] = y2, s[5] = z2;
            s[6] = x1, s[7] = y2, s[8] = z1;
        }
        
        glGenVertexArrays (1, &baseboID);
        glBindVertexArray (baseboID);
        glGenBuffers (1, &baseboID);
        glBindBuffer (GL_ARRAY_BUFFER, baseboID);
        glBufferData (GL_ARRAY_BUFFER, sizeof (base), base, GL_STATIC_DRAW);
        
        glGenVertexArrays (1, &coverboID);
        glBindVertexArray (coverboID);
        glGenBuffers (1, &coverboID);
        glBindBuffer (GL_ARRAY_BUFFER, coverboID);
        glBufferData (GL_ARRAY_BUFFER, sizeof (cover), cover, GL_STATIC_DRAW);
        
        glGenVertexArrays (1, &sideboID);
        glBindVertexArray (sideboID);
        glGenBuffers (1, &sideboID);
        glBindBuffer (GL_ARRAY_BUFFER, sideboID);
        glBufferData (GL_ARRAY_BUFFER, sizeof (side), side, GL_STATIC_DRAW);
        
        GLfloat baseColor[slice*9], sideColor[slice*18];
        for (int i = 0; i < slice*9; i+=3)
            baseColor[i] = 0.75f, baseColor[i+1] = baseColor[i+2] = 0.0f;
        for (int i = 0; i < slice*18; i+=3)
            sideColor[i+1] = 0.5f, sideColor[i] = sideColor[i+2] = 0.0f;
        
        glGenBuffers (1, &basecboID);
        glBindBuffer (GL_ARRAY_BUFFER, basecboID);
        glBufferData (GL_ARRAY_BUFFER, sizeof (baseColor), baseColor, GL_STATIC_DRAW);
        
        glGenBuffers (1, &covercboID);
        glBindBuffer (GL_ARRAY_BUFFER, covercboID);
        glBufferData (GL_ARRAY_BUFFER, sizeof (baseColor), baseColor, GL_STATIC_DRAW);
        
        glGenBuffers (1, &sidecboID);
        glBindBuffer (GL_ARRAY_BUFFER, sidecboID);
        glBufferData (GL_ARRAY_BUFFER, sizeof (sideColor), sideColor, GL_STATIC_DRAW);
    }
    
    virtual void render () override {
        glEnableVertexAttribArray (0);
        glBindBuffer (GL_ARRAY_BUFFER, baseboID);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glEnableVertexAttribArray (1);
        glBindBuffer (GL_ARRAY_BUFFER, basecboID);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glDrawArrays (GL_TRIANGLES, 0, slice * 9);
        glDisableVertexAttribArray (0);
        glDisableVertexAttribArray (1);
        
        glEnableVertexAttribArray (0);
        glBindBuffer (GL_ARRAY_BUFFER, coverboID);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glEnableVertexAttribArray (1);
        glBindBuffer (GL_ARRAY_BUFFER, covercboID);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glDrawArrays (GL_TRIANGLES, 0, slice * 9);
        glDisableVertexAttribArray (0);
        glDisableVertexAttribArray (1);
        
        glEnableVertexAttribArray (0);
        glBindBuffer (GL_ARRAY_BUFFER, sideboID);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glEnableVertexAttribArray (1);
        glBindBuffer (GL_ARRAY_BUFFER, sidecboID);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        glDrawArrays (GL_TRIANGLES, 0, slice * 18);
        glDisableVertexAttribArray (0);
        glDisableVertexAttribArray (1);
    }
    
    virtual void clean () override {
        Object::clean ();
    }

private:
    GLuint baseboID, coverboID, sideboID, basecboID, covercboID, sidecboID;
    int slice;
};
