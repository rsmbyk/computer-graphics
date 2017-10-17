#include <cstdlib>
#include <cstdio>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <common/shader.hpp>
#include <common/controls.hpp>
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);
    glClearColor (0.0f, 0.0f, 0.8f, 0.0f);
    
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    glEnable(GL_CULL_FACE);
    
    GLuint VertexArrayID;
    glGenVertexArrays (1, &VertexArrayID);
    glBindVertexArray (VertexArrayID);
    
    GLuint programID = LoadShaders ("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
    GLuint MatrixID = glGetUniformLocation (programID, "MVP");
    
    // vertex list to draw the cube
    static GLfloat g_vertex_buffer_data[] = {
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
    static GLfloat g_color_buffer_data[6*6*3];
    srand (static_cast <unsigned> (time (0)));
    for (int v = 0; v < 6; v++) {
        GLfloat r, g, b;
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        for (int u = 0; u < 6; u++) {
            g_color_buffer_data[18*v+3*u+0] = r;
            g_color_buffer_data[18*v+3*u+1] = g;
            g_color_buffer_data[18*v+3*u+2] = b;
        }
    }
    
    GLuint vertexbuffer;
    glGenBuffers (1, &vertexbuffer);
    glBindBuffer (GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData (GL_ARRAY_BUFFER, sizeof (g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    GLuint colorbuffer;
    glGenBuffers (1, &colorbuffer);
    glBindBuffer (GL_ARRAY_BUFFER, colorbuffer);
    glBufferData (GL_ARRAY_BUFFER, sizeof (g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    
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
                    g_color_buffer_data[18*v+3*u+0] = r;
                    g_color_buffer_data[18*v+3*u+1] = g;
                    g_color_buffer_data[18*v+3*u+2] = b;
                }
            }
            
            glBufferData (GL_ARRAY_BUFFER, sizeof (g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
        }
        
        glUseProgram (programID);
    
        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        
        glUniformMatrix4fv (MatrixID, 1, GL_FALSE, &MVP[0][0]);
        
        glEnableVertexAttribArray (0);
        glBindBuffer (GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        
        glEnableVertexAttribArray (1);
        glBindBuffer (GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        
        glDrawArrays (GL_TRIANGLES, 0, 12*3);
        
        glDisableVertexAttribArray (0);
        glDisableVertexAttribArray (1);
        
        glfwSwapBuffers (window);
        glfwPollEvents ();
    }
    while (glfwGetKey (window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose (window) == 0);
    
    // Cleanup VBO and shader
    glDeleteBuffers (1, &vertexbuffer);
    glDeleteBuffers (1, &colorbuffer);
    glDeleteProgram (programID);
    glDeleteVertexArrays (1, &VertexArrayID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate ();
    
    return 0;
}

