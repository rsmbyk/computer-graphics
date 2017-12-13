#ifndef COMPUTER_GRAPHICS_CURVE_HPP
#define COMPUTER_GRAPHICS_CURVE_HPP

#include <glm/vec3.hpp>
#include <vector>
#include <map>

using namespace glm;
using namespace std;

class BezierCurve {
public:
    void addAnchorPoint (vec3 ap);
    void addControlPoint (int i, vec3 cp);
    void setFlatness (int f);
    void build (vector<vec3> &bezierPoints);

private:
    void bezierCurve (vector<vec3> &cp, vector<vec3> &bezierPoints);
    vec3 deCasteljau (vector<vec3> &p, float t);
    
    vector<vec3> anchorPoints;
    map<int, vector<vec3> > controlPoints;
    int flatness = 30;
};

#endif // COMPUTER_GRAPHICS_CURVE_HPP
