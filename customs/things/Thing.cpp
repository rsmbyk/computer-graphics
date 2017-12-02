#include "Thing.hpp"

void Thing::add (Object *object) {
    objects.push_back (object);
}

void Thing::onRender () {
    for (Object *obj : objects)
        obj->onRender ();
}

void Thing::onClean () {
    for (Object *obj : objects)
        obj->onClean ();
}

void Thing::onTransform (mat4 T) {
    for (Object *obj : objects)
        obj->transform (T);
}

void Thing::onMeasureMargin () {
    for (Object *obj : objects)
        for (int i = 0; i < 3; i++) {
            margin[0][i] = std::min (margin[0][i], obj->margin[0][i]);
            margin[1][i] = std::max (margin[1][i], obj->margin[1][i]); }
}
