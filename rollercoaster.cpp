#include <glew.h>
#include <glfw3.h>
#include <cstdlib>
#include <ctime>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>
#include <custom/base/Object.hpp>
#include <common/controls.hpp>
#include <common/shader.hpp>
#include <custom/utils/utils.hpp>
#include <custom/utils/pathway.hpp>
#include <cstdio>
#include <algorithm>
#include <grafkom.hpp>
#include <map>

using namespace std;
using namespace grafkom;

GLFWwindow* window;

int random (int imin, int imax) {
    return imin + rand () % (imax-imin+1); // NOLINT
}

float random (float fmin, float fmax) {
    return fmin + (float) rand () / (RAND_MAX / (fmax-fmin)); // NOLINT
}

void generateRandomTree (int n, float height, float planeSize, vector<Object*> &objects) {
    float space[] = {-planeSize/2, 5};
    for (int i = 0; i < n; i++) {
        float x, z;
        x = random (-planeSize/2, planeSize/2);
        
        float s = space[random (0, 1)];
        z = random (s, s+(planeSize/2)-5);
        
        int size = random (5, 10-5+1);
        objects.push_back (new Tree (x, height, z, size));
    }
}

int initGL (const char windowTitle[]) {
    // initialize GLFW. Exit on failed.
    if (!glfwInit ())
        return -1;
    
    glfwWindowHint (GLFW_SAMPLES, 8);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint (GLFW_REFRESH_RATE, 60);
    
    // Open a window in full screen mode
    GLFWmonitor *monitor = glfwGetPrimaryMonitor ();
    const GLFWvidmode* mode = glfwGetVideoMode (monitor);
    window = glfwCreateWindow (mode->width, mode->height, windowTitle, monitor, nullptr);
    glfwSetWindowAspectRatio (window, 1366, 768);
    
    if (window == nullptr) {
        glfwTerminate ();
        return -1;
    }
    
    glfwMakeContextCurrent (window);
    
    // Initialize GLEW
    glewExperimental = (GLboolean) true;
    if (glewInit () != GLEW_OK) {
        glfwTerminate ();
        return -1;
    }
    
    glfwSetInputMode (window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents ();
    glfwSetCursorPos (window, 1366/2, 768/2);
    glClearColor (150/255.0f, 207/255.0f, 234/255.0f, 0);
    
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    glEnable (GL_CULL_FACE);
    return 0;
}

int main (int argc, char **argv) {
    srand (static_cast <unsigned> (time (0))); // NOLINT
    if (initGL ("RollerCoaster") == -1)
        return -1;
    
    GLuint programID = LoadShaders ("shader/TransformVertexShader.vertexshader", "shader/ColorFragmentShader.fragmentshader");
    GLint MatrixID = glGetUniformLocation (programID, "MVP");
    
    // define all the objects here.
    vector<Object*> objects;
    
    float groundLevel = -0.25f;
    float groundSize = 100;
    
    // earth
    Plane earth (groundLevel, groundSize);
    objects.push_back (&earth);
    
    // sun
    Sun sun (groundLevel, groundSize);
    objects.push_back (&sun);
    
    // railway paths
    vector<vec3> controlPoints;
    vector<vec3> paths;
    buildPathFromFile ("paths2.txt", paths, controlPoints);
    
    // rails
    vector<Object*> rails;
    buildRailway (paths, rails);
    
    // print control points defined
    vector<Object> cp;
    for (vec3 path : controlPoints)
        cp.push_back (Cube (path.x, path.y-0.25f, path.z, 0.5f));
    
    // train
    Train train1 (0, 0, 0, 8, 8);
    objects.push_back (&train1);
    train1.setWalkPath (paths, 8);
    
    Train train2 (0, 0, 0, 8, 8);
    objects.push_back (&train2);
    train2.setWalkPath (paths, 8);
    train2.setWalkProgress (100);
    
    // trees
    generateRandomTree (100, groundLevel, groundSize, objects);
    
    // axes
    vector<Object> axes;
    Box x (-100, 100, -0.01f, 0.01f, -0.01f, 0.01f);
    Box y (-0.01f, 0.01f, -100, 100, -0.01f, 0.01f);
    Box z (-0.01f, 0.01f, -0.01f, 0.01f, -100, 100);
    x.setColor ({0, 0, 0});
    y.setColor ({0, 0, 0});
    z.setColor ({0, 0, 0});
    axes.push_back (x);
    axes.push_back (y);
    axes.push_back (z);
    
    // --------------------------------------------------
    // define all object to be used.
    // --------------------------------------------------
    Box box (-16, -8, 3.75f, 4.25f, -2, 2);
    Cube cube (-12, 7, 0, 2.5f);
    Cone cone (5, 5, 0, 1, 3);
    cone.rotateAt ({0, 0, -90}, {0.5f, 0, 0.5f});
    Pyramid pyramid (7, 0, 7, 5, 2, 4);
    Sphere sphere (7, 14, 7, 10);
    Sphere matahari (10, 10, -10, 2);
    Sphere bumi (5, 10, -10, 1);
    Sphere bulan (3, 10, -10, 0.5f);
    Car car (0, 0, 0, 10);
    
    // --------------------------------------------------
    // insert to 'objects' vector.
    // --------------------------------------------------
    objects.push_back (&box);
    objects.push_back (&cube);
    objects.push_back (&cone);
    objects.push_back (&matahari);
    objects.push_back (&bumi);
    objects.push_back (&bulan);
    objects.push_back (&pyramid);
    objects.push_back (&sphere);
    objects.push_back (&car);
    
    // --------------------------------------------------
    // set walk path
    // --------------------------------------------------
    car.setWalkPath (paths, {0.5f, 0, 0.5f}, 7.9f);
    
    // --------------------------------------------------
    // keyboard states
    // --------------------------------------------------
    map<int, bool> state;
    
    // --------------------------------------------------
    // flags
    // --------------------------------------------------
    map<string, bool> flags;
    flags["controlPoints"] = true;
    flags["axes"] = true;
    flags["rails"] = true;
    
    // --------------------------------------------------
    // first render
    // --------------------------------------------------
    for (auto object : objects)
        object->render ();
    
    while (glfwGetKey (window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose (window) == 0) {
        if (glfwGetKey (window, GLFW_KEY_1) == GLFW_PRESS) {
            if (!state[GLFW_KEY_1])
                flags["axes"] = !flags["axes"];
            state[GLFW_KEY_1] = true;
        }
        else state[GLFW_KEY_1] = false;
        
        if (glfwGetKey (window, GLFW_KEY_2) == GLFW_PRESS) {
            if (!state[GLFW_KEY_2])
                flags["controlPoints"] = !flags["controlPoints"];
            state[GLFW_KEY_2] = true;
        }
        else state[GLFW_KEY_2] = false;
    
        if (glfwGetKey (window, GLFW_KEY_3) == GLFW_PRESS) {
            if (!state[GLFW_KEY_3])
                flags["rails"] = !flags["rails"];
            state[GLFW_KEY_3] = true;
        }
        else state[GLFW_KEY_3] = false;
    
        if (glfwGetKey (window, GLFW_KEY_UP) == GLFW_PRESS)
            train1.walkSpeed = std::min (train1.walkSpeed+0.2f, 64.0f);
    
        if (glfwGetKey (window, GLFW_KEY_DOWN) == GLFW_PRESS)
            train1.walkSpeed = std::max (train1.walkSpeed-0.4f, 0.0f);
    
        // --------------------------------------------------
        // do transforms here
        // --------------------------------------------------
        train1.walk ();
        train2.walk ();
        car.walk ();
        box.rotate ({0, 1, 0});
        cube.rotate ({0.75f, 0, 0}, {0, 0, 0});
        cone.rotate ({0, 0.5f, 0}, {0, 0, 0});
        vec3 bumiPrevPos = bumi.center;
        bumi.rotate ({0, 1/6.0, 0}, matahari.center);
        bulan.rotate ({0, 2, 0}, bumiPrevPos);
        bulan.translateTo (bumi.center, bumiPrevPos);
        sphere.scaleAt (vec3 (-0.004f), {0.5f, 0, 0.5f});
        // --------------------------------------------------
        // end
        // --------------------------------------------------
        
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram (programID);
        
        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs ();
        glm::mat4 ProjectionMatrix = getProjectionMatrix ();
        glm::mat4 ViewMatrix = getViewMatrix ();
        glm::mat4 ModelMatrix = glm::mat4 (1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        glUniformMatrix4fv (MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
        for (auto object : objects)
            // render all objects defined
            object->render ();
    
        if (flags["axes"])
            for (auto axis : axes)
                axis.render ();
        
        if (flags["controlPoints"])
            for (auto p : cp)
                p.render ();
        
        if (flags["rails"])
            for (auto rail : rails)
                rail->render ();
        
        glfwSwapInterval (1);
        glfwSwapBuffers (window);
        glfwPollEvents ();
    }
    
    for (auto object : objects)
        object->clean ();
    
    glDeleteProgram (programID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate ();
    
    return 0;
}
