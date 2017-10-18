#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <common/controls.hpp>
#include <common/shader.hpp>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace glm;
GLFWwindow* window;

int main () {
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
    window = glfwCreateWindow (1024, 768, "Grafkom Object DDD", nullptr, nullptr);
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
    
    GLuint cubeVertexArrayID;
    glGenVertexArrays (1, &cubeVertexArrayID);
    glBindVertexArray (cubeVertexArrayID);
    
    GLuint programID = LoadShaders ("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
    GLuint MatrixID = glGetUniformLocation (programID, "MVP");
    
    // vertex list to draw the cube
    static GLfloat cube_buffer[] = {
        // left
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        
        // top
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,

        // bottom
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        // front
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        
        // right
         1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
        
        // rear
         1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f
    };
    
    // One color for each side. Generate random for each execution
    static GLfloat colorBuffer[6*6*3];
    srand (static_cast <unsigned> (time (0)));
    for (int v = 0; v < 6; v++) {
        GLfloat r, g, b;
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        for (int u = 0; u < 6; u++) {
            colorBuffer[18*v+3*u+0] = r;
            colorBuffer[18*v+3*u+1] = g;
            colorBuffer[18*v+3*u+2] = b;
        }
    }
    
    GLuint cubeBufferID;
    glGenBuffers (1, &cubeBufferID);
    glBindBuffer (GL_ARRAY_BUFFER, cubeBufferID);
    glBufferData (GL_ARRAY_BUFFER, sizeof (cube_buffer), cube_buffer, GL_STATIC_DRAW);
    
    GLuint colorBufferID;
    glGenBuffers (1, &colorBufferID);
    glBindBuffer (GL_ARRAY_BUFFER, colorBufferID);
    glBufferData (GL_ARRAY_BUFFER, sizeof (colorBuffer), colorBuffer, GL_STATIC_DRAW);
    
    int timer = 0;
    
    do {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // generate new color combinations every 600 frame
        if (++timer % 600 == 0) {
            timer = 0;
            for (int v = 0; v < 6; v++) {
                GLfloat r, g, b;
                r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                for (int u = 0; u < 6; u++) {
                    colorBuffer[18*v+3*u+0] = r;
                    colorBuffer[18*v+3*u+1] = g;
                    colorBuffer[18*v+3*u+2] = b;
                }
            }
            
            glBufferData (GL_ARRAY_BUFFER, sizeof (colorBuffer), colorBuffer, GL_STATIC_DRAW);
        }
        
        glUseProgram (programID);
    
        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs ();
        glm::mat4 ProjectionMatrix = getProjectionMatrix ();
        glm::mat4 ViewMatrix = getViewMatrix ();
        glm::mat4 ModelMatrix = glm::mat4 (1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        
        glUniformMatrix4fv (MatrixID, 1, GL_FALSE, &MVP[0][0]);
        
        glEnableVertexAttribArray (0);
        glBindBuffer (GL_ARRAY_BUFFER, cubeBufferID);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        
        glEnableVertexAttribArray (1);
        glBindBuffer (GL_ARRAY_BUFFER, colorBufferID);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        
        glDrawArrays (GL_TRIANGLES, 0, 12*3);
        
        glDisableVertexAttribArray (0);
        glDisableVertexAttribArray (1);
        
        glfwSwapBuffers (window);
        glfwPollEvents ();
    }
    while (glfwGetKey (window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose (window) == 0);
    
    // Cleanup VBO and shader
    glDeleteBuffers (1, &cubeBufferID);
    glDeleteBuffers (1, &colorBufferID);
    glDeleteProgram (programID);
    glDeleteVertexArrays (1, &cubeVertexArrayID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate ();
    
    return 0;
}
