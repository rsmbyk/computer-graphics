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
    
    void move (int coord, GLfloat amount) override {
        for (int i = 0; i < objects.size (); i++)
            objects[i]->move (coord, amount);
    }

private:
    std::vector<Object*> objects {};
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
    
    void move (int coord, GLfloat amount) override {
        trunk.move (coord, amount);
        leaves.move (coord, amount);
    }

private:
    Cylinder trunk;
    Cone leaves;
};


class Car : public Object {
public:
    Car (GLfloat x, GLfloat y, GLfloat z, GLfloat size) {
        GLfloat m = multiplier;
        box = (new Box (x-(m*size*4), x+(m*size*4), y, y+(m*size*4), z-(m*size*2), z+(m*size*2)))
            ->setFaceColor (Box::TOP, Color ())
            ->setFaceColor (Box::LEFT, Color ())
            ->setFaceColor (Box::RIGHT, Color ())
            ->setFaceColor (Box::FRONT, Color ())
            ->setFaceColor (Box::REAR, Color ());
        
        connector = (new Box (x-(m*size*5), x-(m*size*4), y+(m*size*0.5f), y+(m*size*1), z-(m*size*0.5f), z+(m*size*0.5f)))
            ->setFaceColor (Color (0, 0, 0, true))
            ->setFaceColor (Box::TOP, Color (20, 20, 20, true));
        
        windows.push_back (
            (new Box (x-(m*size*1.25f), x+(m*size*1.25f), y+(m*size*0.75f), y+(m*size*3.25f), z+(m*size*2), z+(m*size*2)+0.05f))
            ->setFaceColor (Color (200, 200, 200, true))
            ->setFaceColor (Box::FRONT, Color (255, 255, 255, true))
        );
        windows.push_back (
            (new Box (x-(m*size*1.25f), x+(m*size*1.25f), y+(m*size*0.75f), y+(m*size*3.25f), z-(m*size*2)-0.05f, z+(m*size*2)))
            ->setFaceColor (Color (200, 200, 200, true))
            ->setFaceColor (Box::FRONT, Color (255, 255, 255, true))
        );
    }
    
    void render () override {
        box->render ();
        connector->render ();
        for (int i = 0; i < windows.size (); i++)
            windows[i]->render ();
    }
    
    void clean () override {
        box->clean ();
        connector->clean ();
        for (int i = 0; i < windows.size (); i++)
            windows[i]->clean ();
    }
    
    void move (int coord, GLfloat amount) override {
        box->move (coord, amount);
        connector->move (coord, amount);
        for (int i = 0; i < windows.size (); i++)
            windows[i]->move (coord, amount);
    }
    
    static constexpr GLfloat multiplier = 0.1f;
    
private:
    Box *box, *connector;
    std::vector<Object*> windows {};
};


class Train : public Object {
public:
    Train (GLfloat x, GLfloat y, GLfloat z, int length, GLfloat carSize) {
        for (int i = 1; i <= length; i++) {
            GLfloat xNext = x+(i*Car::multiplier*9*carSize);
            cars.push_back (new Car (xNext, y, z, carSize));
        }
    }
    
    void render () override {
//        chimney.render ();
        for (int i = 0; i < cars.size (); i++)
            cars[i]->render ();
    }
    
    void clean () override {
//        chimney.clean ();
        for (int i = 0; i < cars.size (); i++)
            cars[i]->clean ();
    }
    
    void move (int coord, GLfloat amount) override {
//        chimney->move (coord, amount);
        for (int i = 0; i < cars.size (); i++)
            cars[i]->move (coord, amount);
    }

private:
    std::vector<Car*> cars {};
    Cylinder *chimney {};
};
