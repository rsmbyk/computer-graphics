#include <glm/vec3.hpp>
#include <vector>
#include <cmath>
#include "Sphere.hpp"

Sphere::Sphere ()
: Sphere (0, 0, 0, 2) {}

Sphere::Sphere (float x, float y, float z, float r) {
    // mathinsight.org/spherical_coordinates
    
    vec3 coord[N1][N2];
    double radConst = M_PI / 180.0;
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < N2; j++) {
            double a, b, c;
            a = x + r * sin ((j*180.0/N2) * radConst) * cos ((i*360.0/N1) * radConst);
            b = y + r * sin ((j*180.0/N2) * radConst) * sin ((i*360.0/N1) * radConst);
            c = z + r * cos ((j*180.0/N2) * radConst);
            coord[i][j] = vec3 (a, b, c);
        }
    }
    
    
    // this one is not the south side, rather the back side of the sphere.
    // the indexing system of θ and ϕ cause it to end in the back side of
    // the sphere.
    vec3 south (x, y, z-r);
    vec3 north (x, y+r, z);
    std::vector<float> tempBuffer;
    
    for (int i = 0; i < N1; i++) {
        for (int j = 0; j < 3; j++)
            tempBuffer.push_back (north[j]);
        
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 3; k++)
                tempBuffer.push_back (coord[(i+j)%N1][0][k]);
        
        for (int j = 0; j < N2-1; j++) {
            for (int k = 0; k < 3; k++)
                tempBuffer.push_back (coord[i][j][k]);
            for (int k = 0; k < 3; k++)
                tempBuffer.push_back (coord[i][j+1][k]);
            for (int k = 0; k < 3; k++)
                tempBuffer.push_back (coord[(i+1)%N1][j][k]);
            for (int k = 0; k < 3; k++)
                tempBuffer.push_back (coord[(i+1)%N1][j][k]);
            for (int k = 0; k < 3; k++)
                tempBuffer.push_back (coord[i][j+1][k]);
            for (int k = 0; k < 3; k++)
                tempBuffer.push_back (coord[(i+1)%N1][j+1][k]);
        }
        
        for (int k = 0; k < 3; k++)
            tempBuffer.push_back (coord[i%N1][N2-1][k]);
    
        for (int j = 0; j < 3; j++)
            tempBuffer.push_back (south[j]);
        
        for (int k = 0; k < 3; k++)
            tempBuffer.push_back (coord[(i+1)%N1][N2-1][k]);
    }
    
    BUFFER_LENGTH = tempBuffer.size ();
    BUFFER_SIZE = BUFFER_LENGTH * sizeof (float*);
    TRIANGLE_COUNT = BUFFER_LENGTH / 3;
    
    buffer = new float[BUFFER_LENGTH];
    for (int i = 0; i < BUFFER_LENGTH; i++)
        buffer[i] = tempBuffer[i];
    
    init ();
    
    setColor (Color ());
}

void Sphere::setColor (Color color) {
    for (int i = 0; i < BUFFER_LENGTH; i += 3)
        for (int j = 0; j < 3; j++)
            colors[i+j] = color[j];
    updateBuffer ();
}
