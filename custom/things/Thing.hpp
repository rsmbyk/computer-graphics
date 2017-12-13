#ifndef COMPUTER_GRAPHICS_COMPLEXOBJECT_HPP
#define COMPUTER_GRAPHICS_COMPLEXOBJECT_HPP

#include <custom/base/Object.hpp>
#include <vector>

using namespace glm;

/**
 * DO NOT FORGET TO CALL init () METHOD
 * AT THE END OF CONSTRUCTOR TO MAKE SURE
 * IT IS INITIALIZED ANDMEASURED PROPERLY !!!
 */

class Thing : public Object {
public:
    void add (Object *object);
    void onRender () override;
    void onClean () override;
    void onMeasureMargin () override;
    void onTransform (mat4 T) override;

private:
    std::vector<Object*> objects;
};

#endif // COMPUTER_GRAPHICS_COMPLEXOBJECT_HPP
