#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <GL/glew.h>
#include <glfw3.h>
#include <common/controls.hpp>
#include <common/shader.hpp>
#include <customs/shapes.hpp>
#include <customs/things.hpp>
#include <customs/utils/tranform_matrix.hpp>

GLFWwindow* window;

GLfloat random (GLfloat min, GLfloat max) {
    return min + (GLfloat) rand () / (GLfloat (RAND_MAX / (max-min)));
}

void generateRandomTree (int n, GLfloat height, GLfloat planeSize, std::vector<Object*> &objects) {
    GLfloat space[] = {-planeSize/2, 5};
    for (int i = 0; i < n; i++) {
        GLfloat x, z;
        x = random (-planeSize/2, planeSize/2);
        
        GLfloat s = space[rand () % 2];
        z = random (s, s+(planeSize/2)-5);
        
        int size = 5 + rand () % (10-5+1);
        objects.push_back (new Tree (x, height, z, size));
    }
}

int initGL () {
    // initialize GLFW
    if (!glfwInit ()) {
        fprintf (stderr, "Failed to initialize GLFW\n");
        getchar ();
        return -1;
    }
    
    glfwWindowHint (GLFW_SAMPLES, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow (800, 600, "Rollercoaster", nullptr, nullptr);
    if (window == nullptr) {
        getchar ();
        glfwTerminate ();
        return -1;
    }
    glfwMakeContextCurrent (window);
    
    // Initialize GLEW
    glewExperimental = true;
    if (glewInit () != GLEW_OK) {
        fprintf (stderr, "Failed to initialize GLEW\n");
        getchar ();
        glfwTerminate ();
        return -1;
    }
    
    glfwSetInputMode (window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents ();
    glfwSetCursorPos (window, 1024/2, 768/2);
    glClearColor (0.4f, 0.6f, 0.9f, 0.0f);
    
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    glEnable (GL_CULL_FACE);
    return 0;
}

int main () {
    srand (static_cast <unsigned> (time (0)));
    if (initGL () == -1)
        return -1;
    
    GLuint programID = LoadShaders ("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
    GLint MatrixID = glGetUniformLocation (programID, "MVP");
    
    /* define all the objects here. */
    std::vector<Object*> objects;
    
//    objects.push_back (new Cube (5, 0, 0, 2, true));
//    objects.push_back (new Cube (3.6,0.75, 0, 0.45, true));
//    objects.push_back (new Cube (3.8,0.75, 0, 0.45, true));
//    objects.push_back (new Cube (0, 0, 0, 2, true));
//    objects.push_back (new Cube (1.1,0.75, 0, 0.45, true));
//    objects.push_back (new Cube (1.3,0.75, 0, 0.45, true));
//    objects.push_back (new Cube (2.5, 0, 0, 2, true));
//    objects.push_back (new Cube (-1.1,0.75, 0, 0.45, true));
//    objects.push_back (new Cube (-1.3,0.75, 0, 0.45, true));
//    objects.push_back (new Cube (-2.5, 0, 0, 2, true));
//    objects.push_back (new Box (-4.5,-3, 0, 1,-0.9,0.9, true));
//    objects.push_back ((new Prism (-2.5, 2, 0, 6, 1.0, 3.0, true))->setColor (0, Color ()));
    
    // kereta
//    auto *train = new Train (0, 0, 0, 10, 5);
//    objects.push_back ((Object*) train);
    
    // sample tree, drawn next to the train
//    auto tree = new Tree (0, 0, 2, 2);
//    objects.push_back ((Object*) tree);
//
//    // earth
//    objects.push_back (new Plane (0, -0.25f, 0, 50));
//
//    // rail
//    auto *rail = new Box (-25, 25, -0.25f, 0, -1, 1);
//    for (int i = 0; i < 6; i++)
//        rail->setFaceColor (i, Color (64, 64, 64, true));
//    rail->setFaceColor (TOP, Color (80, 80, 80, true));
//    objects.push_back ((Object*) rail);
//
    generateRandomTree (50, -0.25f, 50.0f, objects);
    Cube cube (-5, 2, 0, 4, true);
    Prism prism (10, 2, -10, 6, 2, 4, true);
    Cone cone (8, -6, 0, 2, 4, true);
    Pyramid pyramid (2, 5, 0, 4, 2, 4, true);
    Cylinder cylinder (-20, -20, 20, 2.5, 4, true);
    
    Tree tree (0, -0.8f, 0, 4);

    objects.push_back (&cube);
    objects.push_back (&cone);
    objects.push_back (&pyramid);
    objects.push_back (&cylinder);
    objects.push_back (&prism);
    objects.push_back (new Car (6, 2, 6, 4));
    objects.push_back (&tree);
    objects.push_back (new Sphere (0, 5, 0, 3));
    objects.push_back (new Sun (0, 100));
    objects.push_back (new Plane (0, 0, 0, 100));
    // axis
    objects.push_back (new Box (-100, 100, -0.01f, 0.01f, -0.01f, 0.01f, true));
    objects.push_back (new Box (-0.01f, 0.01f, -100, 100, -0.01f, 0.01f, true));
    objects.push_back (new Box (-0.01f, 0.01f, -0.01f, 0.01f, -100, 100, true));
    
    objects.push_back (new Train (0, 0, 0, 4, 3.5));
    
    while (glfwGetKey (window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose (window) == 0) {
        cube.orbit (1, 0, 0, 0, 0, 0);
        cone.orbit (-1, 0, 0, 0, 0, 0);
        pyramid.rotate (0, 1, 0);
        cylinder.translate (0.02f, 0.02f, -0.02f);
        prism.scale (0.0005f, 0.001f, 0);
        tree.translate (0.005f, 0, 0);
        tree.rotate (2, 0, 0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        glUseProgram (programID);
        
        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs ();
        glm::mat4 ProjectionMatrix = getProjectionMatrix ();
        glm::mat4 ViewMatrix = getViewMatrix ();
        glm::mat4 ModelMatrix = glm::mat4 (1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        glUniformMatrix4fv (MatrixID, 1, GL_FALSE, &MVP[0][0]);
        
        for (int i = 0; i < objects.size (); i++)
            // render all objects defined
            objects[i]->render ();
        
        glfwSwapBuffers (window);
        glfwPollEvents ();
    }
    
    for (int i = 0; i < objects.size (); i++)
        objects[i]->clean ();
    glDeleteProgram (programID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate ();
    
    return 0;
}
