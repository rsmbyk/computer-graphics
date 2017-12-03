#include "pathway.hpp"
#include "BezierCurve.hpp"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <queue>
#include <customs/utils/vector_operations.hpp>
#include <customs/base/Object.hpp>
#include <customs/shapes/Box.hpp>

using namespace glm;
using namespace std;
using namespace grafkom;

void buildPathFromFile (const char * path_list_filename, vector<vec3> &paths) {
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
        vec3 p0, p1;
        p0 = paths[i];
        p1 = paths[i+1];
        float x1, x2, y1, y2, z1, z2;
        float r = (float) length (p1 - p0);
        x1 = p0.x - r;
        x2 = p0.x;
        y1 = p0.y - 0.1f;
        y2 = p0.y + 0.1f;
        z1 = p0.z - 0.5f;
        z2 = p0.z + 0.5f;
        
        if (p1.x > p0.x)
            x1 += r, x2 += r;
    
        vec3 angle = angleVector (p0, p1);
    
        Box *box = new Box (x1, x2, y1, y2, z1, z2);
        box->setColor ({64, 64, 64});
        box->setFaceColor (TOP, {80, 80, 80});
        box->orbit (angle, p0);
//        if (i == 0 || i == 1) {
//            printf ("angle:\n");
//            printVec (angle);
//            if (i == 0)
//                box->orbit ({0, 0, angle.z}, p0);
//            if (i == 1)
//                box->orbit ({0, angle.y, 0}, p0);
//        }
        objects.push_back ((Object*) box);
    }
}
