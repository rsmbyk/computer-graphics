#ifndef COMPUTER_GRAPHICS_COMPLEXOBJECT_HPP
#define COMPUTER_GRAPHICS_COMPLEXOBJECT_HPP

#include <custom/base/Object.hpp>
#include <vector>

using namespace glm;

class Thing : public Object {
public:
    void add (Object *object);
    void onRender () override;
    void onClean () override;
    void onMeasureMargin () override;
    void onTransform (mat4 T) override;

private:
    std::vector<Object*> objects {};
};

#endif // COMPUTER_GRAPHICS_COMPLEXOBJECT_HPP
