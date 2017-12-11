#include "BezierCurve.hpp"
#include "utils.hpp"
#include <custom/base/Object.hpp>

using namespace std;
using namespace grafkom;

void BezierCurve::setFlatness (int f) {
    this->flatness = std::max (0, std::min (100, f));
}

void BezierCurve::addAnchorPoint (vec3 ap) {
    anchorPoints.push_back (ap);
}

void BezierCurve::addControlPoint (int i, vec3 cp) {
    if (i == -1)
        controlPoints[anchorPoints.size ()-1].push_back (cp);
    else
        controlPoints[i].push_back (cp);
}

vec3 BezierCurve::deCasteljau (vector<vec3> &p, float t) {
    if (p.size () == 1)
        return p[0];
    
    vector<vec3> q;
    for (int i = 0; i < p.size () - 1; i++)
        q.push_back ((p[i] * (1-t)) + (p[i+1] * t));
    
    return deCasteljau (q, t);
}

void BezierCurve::bezierCurve (vector<vec3> &p, vector<vec3> &bezierPoints) {
    for (int i = 0; i <= flatness; i++)
        bezierPoints.push_back (deCasteljau (p, 1.0f / flatness * i));
}

void BezierCurve::build (vector<vec3> &bezierPoints) {
    for (int i = 0; i < anchorPoints.size ()-1; i++) {
        vector<vec3> p;
        p.push_back (anchorPoints[i]);
        for (vec3 j : controlPoints[i])
            p.push_back (j);
        p.push_back (anchorPoints[i+1]);
        bezierCurve (p, bezierPoints);
    }
}
