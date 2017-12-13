#include "Tree.hpp"

Tree::Tree (float x, float y, float z, int size)
: Tree (x, y, z, size*0.1f, size*0.4f) {}

Tree::Tree (float x, float y, float z, float r, float height) {
    trunk = new Cylinder (x, y, z, r/5, height/3);
    trunk->setSideColor ({81, 66, 55});
    trunk->setBaseColor ({103, 84, 78});
    add (trunk);
    
    leaves = new Cone (x, y+(height/3), z, r, height*2/3);
    leaves->setSideColor ({33, 65, 32});
    leaves->setBaseColor ({24, 48, 2});
    add (leaves);
    
    init ();
}
