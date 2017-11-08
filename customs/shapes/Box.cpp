#include <GL/glew.h>
#include "Box.hpp"

Box::Box (bool shuffleColor)
: Box (-1, 1, -1, 1, -1, 1, shuffleColor) {}

Box::Box (GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2, bool shuffleColor)
: Object (x1, x2, y1, y2, z1, z2) {
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
    
    buffer = new GLfloat[BUFFER_LENGTH] {
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
    glBufferData (GL_ARRAY_BUFFER, BUFFER_LENGTH*sizeof (GLfloat*), buffer, GL_STATIC_DRAW);
    
    // Initial color for all faces of the box is black.
    // It can be overridden by calling @setFaceColor method.
    colors = new GLfloat[BUFFER_LENGTH];
        for (int i = 0; i < BUFFER_LENGTH; i++)
    colors[i] = 0.0f;
    
    // if size parameter of glBufferData didn't use sizeof (),
    // it has to be length of color array multiplied by 4.
    // Still figuring out what this number (4) means. \:
    //
    // EDIT: confirmed, lol :p. 4 is length of bit of its data
    //       type.
    glGenBuffers (1, &cboID);
    glBindBuffer (GL_ARRAY_BUFFER, cboID);
    glBufferData (GL_ARRAY_BUFFER, BUFFER_LENGTH*sizeof (GLfloat*), colors, GL_STATIC_DRAW);
    
    if (shuffleColor)
        for (int i = 0; i < 6; i++)
            setFaceColor (i, Color (true));
}

void Box::render () {
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    
    glEnableVertexAttribArray (1);
    glBindBuffer (GL_ARRAY_BUFFER, cboID);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); // NOLINT
    
    // 6 faces, each 2 triangles with 3 vertex
    glDrawArrays (GL_TRIANGLES, 0, 6*2*3);
    
    glDisableVertexAttribArray (0);
    glDisableVertexAttribArray (1);
}

void Box::clean () {
    glDeleteVertexArrays (1, &vaoID);
    glDeleteBuffers (1, &vboID);
    glDeleteBuffers (1, &cboID);
}

Box *Box::setFaceColor (int face, Color color) {
    for (int i = 0; i < 6; i++)
        colors[18*face+3*i+0] = color.r,
        colors[18*face+3*i+1] = color.g,
        colors[18*face+3*i+2] = color.b;
    glBindBuffer (GL_ARRAY_BUFFER, cboID);
    glBufferData (GL_ARRAY_BUFFER, BUFFER_LENGTH*sizeof (GLfloat*), colors, GL_STATIC_DRAW);
    return this;
}

void Box::move (int axis, GLfloat amount) {
    for (int i = 0; i < BUFFER_LENGTH; i+=3)
        buffer[i+axis] += amount;
    glBindBuffer (GL_ARRAY_BUFFER, vboID);
    glBufferData (GL_ARRAY_BUFFER, BUFFER_LENGTH*sizeof (GLfloat*), buffer, GL_STATIC_DRAW);
}

void Box::rotate (GLfloat x, GLfloat y, GLfloat z) {

}

void Box::scale (GLfloat x, GLfloat y, GLfloat z) {

}


