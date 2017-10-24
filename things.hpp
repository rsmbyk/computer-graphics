#include "objects.hpp"


class ComplexObject : public Object {
public:
    void add (Object *object) {
        objects.push_back (object);
    }
    
    void render () override {
        for (int i = 0; i < objects.size (); i++)
            objects[i]->render ();
    }
    
    void clean () override {
        for (int i = 0; i < objects.size (); i++)
            objects[i]->clean ();
    }

private:
    std::vector<Object*> objects;
};


class Tree : public Object {
public:
    Tree (GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat height) {
        trunk = Cylinder (x, y, z, r/5, height/3);
        trunk.setColor (Color (81, 66, 55, true));
        
        leaves = Cone (x, y+(height/3), z, r, height*2/3);
        leaves.setSideColor (Color (33, 65, 32, true));
        leaves.setBaseColor (Color (24, 48, 2, true));
    }
    
    Tree (GLfloat x, GLfloat y, GLfloat z, int size)
    : Tree (x, y, z, size*0.1f, size*0.4f) {}
    
    void render () override {
        trunk.render ();
        leaves.render ();
    }
    
    void clean () override {
        trunk.clean ();
        leaves.clean ();
    }

private:
    Cylinder trunk = Cylinder (0, 0, 0, 0, 0);
    Cone leaves = Cone (0, 0, 0, 0, 0);
};
