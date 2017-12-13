#include "pathway.hpp"
#include "BezierCurve.hpp"
#include "utils.hpp"
#include <fstream>
#include <sstream>
#include <queue>
#include <custom/shapes/Box.hpp>

using namespace glm;
using namespace std;
using namespace grafkom;

void buildPathFromFile (const char *path_list_filename, vector<vec3> &paths, vector<vec3> &controlPoints) {
    ifstream file;
    file.open (path_list_filename);
    
    float x, y, z, t;
    int o;
    vector<pair<int, vec3> > points;
    priority_queue<float, vector<float>, greater<> > pendingCP;
    string line;
    
    while (getline (file, line)) {
        stringstream ss (line);
        ss >> x >> y >> z >> o;
        vec3 p (x, y, z);
        controlPoints.push_back (p);
        
        if (o == -2)
            pendingCP.push (0.9);
    
        while (!pendingCP.empty ()) {
            vec3 cp = between (points[points.size ()-1].second, p, pendingCP.top ());
            points.emplace_back (0, cp);
            pendingCP.pop ();
        }
        
        points.emplace_back (o > 0, p);
        
        if (o == -2)
            pendingCP.push (0.1);
        
        while (ss >> t)
            pendingCP.push (t);
    }
    
    BezierCurve bezier;
    
    for (pair<int, vec3> &point : points)
        if (point.first == 1)
            bezier.addAnchorPoint (point.second);
        else
            bezier.addControlPoint (-1, point.second);
    
    bezier.build (paths);
}

void buildRailway (vector<vec3> &paths, vector<Object*> &objects) {
    for (int i = 0; i < paths.size ()-1; i++) {
        vec3 p0 = paths[i];
        vec3 p1 = paths[i+1];
        vec3 angle = angleVector (p0, p1);
        
        auto rail = new Box (0, vecLength (p1 - p0), -0.1f, 0, -0.5f, 0.5f);
        rail->setColor ({64, 64, 64});
        rail->setFaceColor (TOP, {80, 80, 80});
        rail->translate (p0);
        rail->rotate (angle, p0);
        objects.push_back (rail);
    }
}
