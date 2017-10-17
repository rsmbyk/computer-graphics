#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

const double PI = 3.141592653589793;
int theta = 0;
int blueHex = 0;
int blueHexChangeSpeed = 4;

void draw_circle (int r, int jumlah_titik, int x_center, int y_center) {
    glBegin (GL_POLYGON);
    for (int i = 0; i <= 360; i++){
        float sudut = i * (2 * PI / jumlah_titik);
        float x = x_center + r * cos (sudut);
        float y = y_center + r * sin (sudut);
        glVertex2f (x, y);
    }
    glEnd();
}

void renderScene (void) {
    glClear (GL_COLOR_BUFFER_BIT);
    theta = (theta + 1) % 360;
    blueHex = (blueHex + blueHexChangeSpeed);
    if (blueHex == 100 || blueHex == 0) blueHexChangeSpeed *= -1;
    
    double rad = theta * PI / 180;
    glColor3f (1.0, 0.0, 0.0); // red
    draw_circle (30, 70, 200 * cos (rad), sin (rad) * 200);
    glColor3f (0.0, 0.0, blueHex / 100.0); // blue
    draw_circle (100, 100, 0, 0);
    glFlush ();
}

void idle () {
    static int lastTime = 0;
    int time = glutGet (GLUT_ELAPSED_TIME);
    
    if (lastTime == 0 || time >= lastTime + 50) {
        lastTime = time;
        glutPostRedisplay ();
    }
}

void visible (int vis) {
    glutIdleFunc (vis == GLUT_VISIBLE ? idle : NULL);
}

int main (int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (640, 480);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Lingkaran Berputar v:");
    gluOrtho2D (-320.0, 320.0, -240.0, 240.0);
    glutDisplayFunc (renderScene);
    glutVisibilityFunc (visible);
    glutMainLoop ();
}


