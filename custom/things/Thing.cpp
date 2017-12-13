#include <cstdio>
#include "Thing.hpp"

void Thing::add (Object *object) {
    objects.push_back (object);
}

void Thing::onRender () {
    for (auto obj : objects)
        obj->render ();
}

void Thing::onClean () {
    for (auto obj : objects)
        obj->clean ();
}

void Thing::onTransform (mat4 T) {
    for (auto obj : objects)
        obj->transform (T);
}

void Thing::onMeasureMargin () {
    for (auto obj : objects)
        for (int i = 0; i < 3; i++)
            margin[0][i] = std::min (margin[0][i], obj->margin[0][i]),
            margin[1][i] = std::max (margin[1][i], obj->margin[1][i]);
}
