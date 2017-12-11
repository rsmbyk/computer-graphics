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
    
    glfwWindowHint (GLFW_SAMPLES, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow (800, 600, windowTitle, nullptr, nullptr);
    
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
    glfwSetCursorPos (window, 1024/2, 768/2);
    glClearColor (150/255.0f, 207/255.0f, 234/255.0f, 0);
    
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_GEQUAL);
    glEnable (GL_CULL_FACE);
    return 0;
}

void printMat42 (mat4 m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            printf ("%.12f ", m[i][j]);
        printf ("\n");
    }
}

int main (int argc, char **argv) {
//    printf ("atan (1): %f\n", atan (1));
//    printf ("atan (1): %f\n", toDegree (atan (1)));
//    printf ("atan (1): %f\n", toRadian (atan (1)));
//    printf ("--");
//    printVec3 (angleVector (vec3 {0, 0, 0}, vec3 (2, 0, 4)));
//    printf ("--");
//    double rad = M_PI / 180.0;
//    vec3 v0 ({0, 0, 0});
//    vec3 v1 ({0, 90*rad, 0});
//    vec3 v2 ({45*rad, 0, 0*rad});
//    quat q0 (v0);
//    quat q1 = quat (v1) * quat (v2);
//    quat q2 = quat (v2);
//    printVec4 (quat (v1));
//    printVec4 (quat (v2));
//    printVec4 (q0);
//    printVec4 (q1);
//    printVec4 (q2);
//    mat4 m0 = toMat4 (q0);
//    mat4 m1 = toMat4 (q1);
//    mat4 m2 = toMat4 (q2);
//    printf ("\n");
//    printMat42 (toMat4 (q0)); printf ("\n");
//    printMat42 (toMat4 (q1)); printf ("\n");
//    printMat42 (toMat4 (q2)); printf ("\n");
//
//    vec4 p (3, 0, 0, 1);
//    printVec4 (p * m0);
//    printVec4 (p * m1);
//    printVec4 (p * m2);
//
//    printVec4 ((p * m0) * toMat4 (inverse (q0)));
//
//    return 0;
    printf ("\n");
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
    buildPathFromFile ("paths.txt", paths, controlPoints);
    
    // rails
    buildRailway (paths, objects);
    
    // print control points defined
    for (vec3 path : controlPoints)
        objects.push_back (new Cube (path.x, path.y-0.25f, path.z, 0.5f));
    
    // train
    Train train (0, 0, 0, 4, 10);
    objects.push_back (&train);
    
    // trees
    generateRandomTree (50, groundLevel, groundSize, objects);
    
    Box box (-16, -8, 3.75f, 4.25f, -2, 2);
    Cube cube (-12, 7, 0, 2.5f);
    Cone cone (5, 5, 0, 1, 3);
    cone.rotateAt ({0, 0, -90}, {0.5f, 0, 0.5f});
    Pyramid pyramid (7, 0, 7, 5, 2, 4);
    Sphere sphere (7, 14, 7, 10);
    Sphere matahari (10, 10, -10, 2);
    Sphere bumi (5, 10, -10, 1);
    Sphere bulan (3, 10, -10, 0.5f);
    Tree tree (0, 0, 0, 5);
    Car car (0, 0, 0, 2);
    
    objects.push_back (&box);
    objects.push_back (&cube);
    objects.push_back (&cone);
    objects.push_back (&matahari);
    objects.push_back (&bumi);
    objects.push_back (&bulan);
    objects.push_back (&pyramid);
    objects.push_back (&sphere);
    objects.push_back (&tree);
    objects.push_back (&car);
//    objects.push_back (&cone);
//    objects.push_back (&cylinder);
//    objects.push_back (&prism);
//    objects.push_back (&tree);
//    objects.push_back (&sphere2);
//    objects.push_back (&sphere3);
//    objects.push_back (&sphere4);
    
    // axes
    Box x (-100, 100, -0.01f, 0.01f, -0.01f, 0.01f);
    Box y (-0.01f, 0.01f, -100, 100, -0.01f, 0.01f);
    Box z (-0.01f, 0.01f, -0.01f, 0.01f, -100, 100);
    x.setColor ({0, 0, 0});
    y.setColor ({0, 0, 0});
    z.setColor ({0, 0, 0});
    objects.push_back (&x);
    objects.push_back (&y);
    objects.push_back (&z);
    
    for (auto object : objects)
        object->render ();
    
    train.setWalkPath (paths, 16);
    tree.setWalkPath (paths, {0.5f, 0, 0.5f}, 16);
    car.setWalkPath (paths, {0.5f, 0, 0.5f}, 16);
    
    while (glfwGetKey (window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose (window) == 0) {
        
        box.rotate ({0, 1, 0});
        cube.rotate ({0.75f, 0, 0}, {0, 0, 0});
        cone.rotate ({0, 0.5f, 0}, {0, 0, 0});
        vec3 bumiPrevPos = bumi.center;
        bumi.rotate ({0, 1/6.0, 0}, matahari.center);
        bulan.rotate ({0, 2, 0}, bumiPrevPos);
        bulan.translateTo (bumi.center, bumiPrevPos);
        sphere.scaleAt (vec3 (-0.004f), {0.5f, 0, 0.5f});
        train.walk ();
        tree.walk ();
        car.walk ();
        
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
