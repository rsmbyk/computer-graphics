#include <windows.h>
#include <GL/glut.h>
#include <ctime>
#include <cmath>

void randomColor () {
    glColor3f (static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
               static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
               static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

void drawQuad (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    glBegin (GL_QUADS);
    randomColor ();
    glVertex2i (x1, y1);
    glVertex2i (x2, y2);
    glVertex2i (x3, y3);
    glVertex2i (x4, y4);
    glEnd();
    glBegin (GL_LINE_LOOP);
    glColor3f (0.0f, 0.0f, 0.0f);
    glVertex2i (x1, y1);
    glVertex2i (x2, y2);
    glVertex2i (x3, y3);
    glVertex2i (x4, y4);
    glEnd();
}

void drawQuad (int xl, int xr, int yl, int yu) {
    drawQuad (xl, yl, xr, yl, xr, yu, xl, yu);
}

void drawTriangle (int u, int b, int l, int r) {
    glBegin (GL_TRIANGLES);
    randomColor ();
    glVertex2i ((l + r) / 2, u);
    glVertex2i (l, b);
    glVertex2i (r, b);
    glEnd ();
    glBegin (GL_LINE_LOOP);
    glColor3f (0.0f, 0.0f, 0.0f);
    glVertex2i ((l + r) / 2, u);
    glVertex2i (l, b);
    glVertex2i (r, b);
    glEnd();
}

void drawCircle (int r, int jumlah_titik, int x_center, int y_center) {
    const double PI = 3.141592653589793;
    glBegin (GL_POLYGON);
    randomColor ();
    for (int i = 0; i <= 360; i++) {
        double sudut = i * (2 * PI / jumlah_titik);
        double x = x_center + r * cos (sudut);
        double y = y_center + r * sin (sudut);
        glVertex2d (x, y);
    }
    glEnd();
}

void drawDotCircle (int r, int jumlah_titik, int x_center, int y_center) {
    const double PI = 3.141592653589793;
    for (int i = 0; i <= 360; i++) {
        glBegin (GL_POINTS);
        double sudut = i * (2 * PI / jumlah_titik);
        double x = x_center + r * cos (sudut);
        double y = y_center + r * sin (sudut);
        glVertex2d (x, y);
    }
    glEnd();
}

void display () {
    glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT);
    
    drawQuad (20, 60, 20, 60);
    drawQuad (60, 130, 20, 60);
    drawTriangle (90, 60, 20, 60);
    drawQuad (40, 90, 60, 60, 130, 60, 110, 90);
    drawQuad (30, 50, 20, 45);
    drawQuad (75, 115, 30, 50);
    drawCircle (10, 360, 20, 130);
    drawDotCircle (13, 16, 20, 130);
    
    glFlush ();
}

int main (int argc, char** argv) {
    srand (static_cast <unsigned> (time (0)));
    glutInit (&argc, argv);
    glutCreateWindow ("roemah");
    glutInitWindowSize (640, 640);
    glutInitWindowPosition (50, 50);
    gluOrtho2D (0.0, 150.0, 0.0, 150.0);
    glPointSize (2.0);
    glutDisplayFunc (display);
    glutMainLoop ();
    return 0;
}
