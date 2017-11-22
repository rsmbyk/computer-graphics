#ifndef COMPUTER_GRAPHICS_COMPLEXOBJECT_HPP
#define COMPUTER_GRAPHICS_COMPLEXOBJECT_HPP

#include <vector>
#include <customs/base/Object.hpp>

using namespace glm;

class Thing : public Object {
public:
    Thing ();
    void add (Object *object);
    
    void render () override;
    void clean () override;
    void transform (mat4 T, int type) override;
    void measure () override;

private:
    std::vector<Object*> objects {};
};

#endif // COMPUTER_GRAPHICS_COMPLEXOBJECT_HPP
