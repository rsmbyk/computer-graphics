#include "Tree.hpp"

Tree::Tree (GLfloat x, GLfloat y, GLfloat z, int size)
: Tree (x, y, z, size*0.1f, size*0.4f) {}

Tree::Tree (GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height)
: Object (x-(r/2), x+(r/2), y, y+height, z-(r/2), z+(r/2)) {
    trunk = Cylinder (x, y, z, r/5, height/3);
    trunk.setSideColor (Color (81, 66, 55, true));
    
    leaves = Cone (x, y+(height/3), z, r, height*2/3);
    leaves.setSideColor (Color (33, 65, 32, true));
    leaves.setBaseColor (Color (24, 48, 2, true));
}

void Tree::render () {
    trunk.render ();
    leaves.render ();
}

void Tree::clean () {
    trunk.clean ();
    leaves.clean ();
}

void Tree::move (int coord, GLfloat amount) {
    trunk.move (coord, amount);
    leaves.move (coord, amount);
}

void Tree::rotate (GLfloat x, GLfloat y, GLfloat z) {

}

void Tree::scale (GLfloat x, GLfloat y, GLfloat z) {

}
