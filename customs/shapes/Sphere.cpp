#include <glm/vec3.hpp>
#include <cmath>
#include <vector>
#include <cstdio>
#include <GL/glew.h>
#include "Sphere.hpp"

Sphere::Sphere ()
: Sphere (0, 0, 0, 4) {}

Sphere::Sphere (GLfloat x, GLfloat y, GLfloat z, GLfloat r)
: Object (x-(r/2), x+(r/2), y, y+r, z-(r/2), z+(r/2)) {
    int N1, N2;
    N1 = 45;
    N2 = 30;
    vec3 coord[N1][N2];
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < N2; j++) {
            double a, b, c;
            a = x + r * sin ((j*180.0/N2)*M_PI/180.0) * cos ((i*360.0/N1)*M_PI/180.0);
            b = y + r * sin ((j*180.0/N2)*M_PI/180.0) * sin ((i*360.0/N1)*M_PI/180.0);
            c = z + r * cos ((j*180.0/N2)*M_PI/180.0);
            coord[i][j] = vec3 (a, b, c);
        }
    }
    
    vec3 north (x, y+r, z);
    vec3 south (x, y, z);
    std::vector<GLfloat> buffer;
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < 3; j++)
            buffer.push_back (north[j]);
        
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 3; k++)
                buffer.push_back (coord[(i+j)%N1][0][k]);
        
        for (int j = 0; j < N2-1; j++) {
            for (int k = 0; k < 3; k++)
                buffer.push_back (coord[i][j][k]);
            for (int k = 0; k < 3; k++)
                buffer.push_back (coord[i][j+1][k]);
            for (int k = 0; k < 3; k++)
                buffer.push_back (coord[(i+1)%N1][j][k]);
            for (int k = 0; k < 3; k++)
                buffer.push_back (coord[(i+1)%N1][j][k]);
            for (int k = 0; k < 3; k++)
                buffer.push_back (coord[i][j+1][k]);
            for (int k = 0; k < 3; k++)
                buffer.push_back (coord[(i+1)%N1][j+1][k]);
        }
        
        for (int j = 0; j < 3; j++)
            buffer.push_back (south[j]);
        
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 3; k++)
                buffer.push_back (coord[(i+j)%N1][N2-1][k]);
    }
    
    printf ("buffer size: %d\n", buffer.size ());
    BUFFER_LENGTH = buffer.size ();
    BUFFER_SIZE = BUFFER_LENGTH * sizeof (GLfloat*);
    this->buffer = new GLfloat[buffer.size ()];
    for (int i = 0; i < BUFFER_LENGTH; i++)
        this->buffer[i] = buffer[i];
    
    glGenVertexArrays (1, &vaoID);
    glBindVertexArray (vaoID);
    glGenBuffers (1, &vboID);
    glBindBuffer (GL_ARRAY_BUFFER, vboID);
    glBufferData (GL_ARRAY_BUFFER, BUFFER_SIZE, this->buffer, GL_STATIC_DRAW);
    
    colors = new GLfloat[buffer.size ()];
    for (int i = 0; i < buffer.size (); i++)
        colors[i] = 0.0f;
    
    glGenBuffers (1, &cboID);
    glBindBuffer (GL_ARRAY_BUFFER, cboID);
    glBufferData (GL_ARRAY_BUFFER, BUFFER_LENGTH, colors, GL_STATIC_DRAW);
    
    _measure ();
}

void Sphere::render () {
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    
    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, cboID);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    
    // 6 faces, each 2 triangles with 3 vertex
    glDrawArrays (GL_TRIANGLES, 0, BUFFER_LENGTH / 3);
    
    glDisableVertexAttribArray (0);
    glDisableVertexAttribArray (1);
}

void Sphere::clean () {
    glDeleteVertexArrays (1, &vaoID);
    glDeleteBuffers (1, &vboID);
    glDeleteBuffers (1, &cboID);
}

void Sphere::transform (mat4 T, int type) {
    for (int i = 0; i < BUFFER_LENGTH; i += 3) {
        vec4 res = vec4 (buffer[i], buffer[i+1], buffer[i+2], 1) * T;
        for (int j = 0; j < 3; j++)
            buffer[i+j] = res[j];
    }
    
    glBindBuffer (GL_ARRAY_BUFFER, vboID);
    glBufferData (GL_ARRAY_BUFFER, BUFFER_SIZE, buffer, GL_STATIC_DRAW);
}

void Sphere::measure () {
    for (int i = 0; i < BUFFER_LENGTH; i += 3) {
        for (int j = 0; j < 3; j++) {
            margin[j][0] = std::min (margin[j][0], buffer[i+j]);
            margin[j][1] = std::max (margin[j][1], buffer[i+j]);
        }
    }
}


