#ifndef COMPUTER_GRAPHICS_COMPLEXOBJECT_HPP
#define COMPUTER_GRAPHICS_COMPLEXOBJECT_HPP

#include <vector>
#include <customs/base/Object.hpp>

class ComplexObject : public Object {
public:
    ComplexObject ();
    void add (Object *object);
    
    void render () override;
    void clean () override;
    void move (int coord, GLfloat amount) override;
    void rotate (GLfloat x, GLfloat y, GLfloat z) override;
    void scale (GLfloat x, GLfloat y, GLfloat z) override;

private:
    std::vector<Object*> objects {};
};

#endif // COMPUTER_GRAPHICS_COMPLEXOBJECT_HPP
