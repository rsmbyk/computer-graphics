#include "Tree.hpp"

Tree::Tree (GLfloat x, GLfloat y, GLfloat z, int size)
: Tree (x, y, z, size*0.1f, size*0.4f) {}

Tree::Tree (GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height) {
    trunk = Cylinder (x, y, z, r/5, height/3);
    trunk.setSideColor (Color (81, 66, 55, true));

    leaves = Cone (x, y+(height/3), z, r, height*2/3);
    leaves.setSideColor (Color (33, 65, 32, true));
    leaves.setBaseColor (Color (24, 48, 2, true));
    
    add (&trunk);
    add (&leaves);
    _measure ();
}
