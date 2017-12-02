#include <GL/glew.h>
#include "Box.hpp"

Box::Box ()
: Box (-2, 2, -0.5f, 0.5f, -1, 1) {}

Box::Box (float x1, float x2, float y1, float y2, float z1, float z2) {
    // As we already knew in elementary school, a box has 8 vertices.
    // These vertices will be used to build buffer for the box
    // which use the same 8 vertices multiple times.
    vec3 v[8];
    v[0] = vec3 (x1, y1, z2);
    v[1] = vec3 (x2, y1, z2);
    v[2] = vec3 (x2, y1, z1);
    v[3] = vec3 (x1, y1, z1);
    v[4] = vec3 (x1, y2, z2);
    v[5] = vec3 (x2, y2, z2);
    v[6] = vec3 (x2, y2, z1);
    v[7] = vec3 (x1, y2, z1);
    
    // 6 faces, each 2 triangles with 3 vertices
    TRIANGLE_COUNT = 36;
    BUFFER_LENGTH = TRIANGLE_COUNT * 3;
    BUFFER_SIZE = BUFFER_LENGTH * sizeof (float*);
    
    buffer = new float[BUFFER_LENGTH] {
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
    
    init ();
    
    for (int i = 0; i < 6; i++)
        setFaceColor (i, Color ());
}

void Box::setFaceColor (int face, Color color) {
    for (int i = 0; i < 18; i += 3)
        colors[18*face+i+0] = color.r,
        colors[18*face+i+1] = color.g,
        colors[18*face+i+2] = color.b;
    glBindBuffer (GL_ARRAY_BUFFER, cboID);
    glBufferData (GL_ARRAY_BUFFER, BUFFER_SIZE, colors, GL_STATIC_DRAW);
}

void Box::setColor (Color color) {
    for (int i = 0; i < 6; i++)
        setFaceColor (i, color);
}
