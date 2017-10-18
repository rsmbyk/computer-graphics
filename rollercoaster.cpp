#include "objects.hpp"

using namespace glm;
GLFWwindow* window;

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
    window = glfwCreateWindow (1024, 768, "Rollercoaster", nullptr, nullptr);
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
    if (initGL () == -1)
        return -1;
    
    GLuint programID = LoadShaders ("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
    GLuint MatrixID = glGetUniformLocation (programID, "MVP");
    
    /* define all the objects here. */
    std::vector<Object*> objets;
    objets.push_back (new Cube (5, 0, 0, 2));
    objets.push_back (new Cube (3.6,0.75, 0, 0.45));
    objets.push_back (new Cube (3.8,0.75, 0, 0.45));
    objets.push_back (new Cube (0, 0, 0, 2));
    objets.push_back (new Cube (1.1,0.75, 0, 0.45));
    objets.push_back (new Cube (1.3,0.75, 0, 0.45));
    objets.push_back (new Cube (2.5, 0, 0, 2));
    objets.push_back (new Cube (-1.1,0.75, 0, 0.45));
    objets.push_back (new Cube (-1.3,0.75, 0, 0.45));
    objets.push_back (new Cube (-2.5, 0, 0, 2));
    objets.push_back (new Box (-4.5,-3, 0, 1,-0.9,0.9));
    Box *rel = new Box (-7,7, -0.25, 0,-1,1);
    rel->setSideColor (Box::TOP, 0.5, 0.5, 0.5);
    rel->setSideColor (Box::BOTTOM, 0.5, 0.5, 0.5);
    rel->setSideColor (Box::LEFT, 0.5, 0.5, 0.5);
    rel->setSideColor (Box::RIGHT, 0.5, 0.5, 0.5);
    rel->setSideColor (Box::FRONT, 0.5, 0.5, 0.5);
    rel->setSideColor (Box::REAR, 0.5, 0.5, 0.5);
    objets.push_back ((Object*) rel);
    objets.push_back (new Plane (0, -0.25, 0, 50));
    objets.push_back (new Cylinder (-2.5, 2, 0, 0.5,1, 100));
    
    do {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram (programID);
        
        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs ();
        glm::mat4 ProjectionMatrix = getProjectionMatrix ();
        glm::mat4 ViewMatrix = getViewMatrix ();
        glm::mat4 ModelMatrix = glm::mat4 (1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        
        glUniformMatrix4fv (MatrixID, 1, GL_FALSE, &MVP[0][0]);
        for (int i = 0; i < objets.size (); i++)
            // render all objects defined
            objets[i]->render ();
        
        glfwSwapBuffers (window);
        glfwPollEvents ();
    }
    while (glfwGetKey (window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose (window) == 0);
    
    for (int i = 0; i < objets.size (); i++)
        objets[i]->clean ();
    glDeleteProgram (programID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate ();
    
    return 0;
}
