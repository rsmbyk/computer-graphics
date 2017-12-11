//#include <cstdio>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include <GL/glew.h>
//#include <glfw3.h>
//#include <common/controls.hpp>
//#include <common/shader.hpp>
//#include <custom/shapes.hpp>
//#include <custom/utils/tranform_matrix.hpp>
//#include <glm/gtx/rotate_vector.hpp>
//
//GLFWwindow* window;
//GLfloat xrot, yrot;
//
//void keyboard_callback () {
//    if (glfwGetKey (window, GLFW_KEY_UP) == GLFW_PRESS)
//        xrot += 0.01f;
//    if (glfwGetKey (window, GLFW_KEY_DOWN) == GLFW_PRESS)
//        xrot -= 0.01f;
//    if (glfwGetKey (window, GLFW_KEY_RIGHT) == GLFW_PRESS)
//        yrot -= 0.01f;
//    if (glfwGetKey (window, GLFW_KEY_LEFT) == GLFW_PRESS)
//        yrot += 0.01f;
//}
//
//int initGL () {
//    vec4 pos (2, 2, 2, 1);
//    mat4 T0, R, Tb;
//    T0 = translation_matrix (-1, -1, -1);
//    R = rotation_matrix (0, 0, 0.01f);
//    Tb = translation_matrix (1, 1, 1);
//    vec4 res = T0 * R * Tb * pos;
//    for (int j = 0; j < 4; j++)
//        printf ("%f ", res[j]);
//    printf ("\n");
//    printf ("\n");
//    
//    vec3 pos2 (2, 2, 2);
//    mat4 m2 = glm::translate (mat4 (-1), pos2);
//    vec4 res2 = rotateZ (pos, 0.01f);
//    for (int j = 0; j < 4; j++)
//        printf ("%f ", res2[j]);
//    printf ("\n");
//    
//    // initialize GLFW
//    if (!glfwInit ()) {
//        fprintf (stderr, "Failed to initialize GLFW\n");
//        getchar ();
//        return -1;
//    }
//    
//    glfwWindowHint (GLFW_SAMPLES, 4);
//    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    
//    // Open a window and create its OpenGL context
//    window = glfwCreateWindow (800, 600, "Rollercoaster", nullptr, nullptr);
//    if (window == nullptr) {
//        getchar ();
//        glfwTerminate ();
//        return -1;
//    }
//    glfwMakeContextCurrent (window);
//    
//    // Initialize GLEW
//    glewExperimental = true;
//    if (glewInit () != GLEW_OK) {
//        fprintf (stderr, "Failed to initialize GLEW\n");
//        getchar ();
//        glfwTerminate ();
//        return -1;
//    }
//    
//    glfwSetInputMode (window, GLFW_STICKY_KEYS, GL_TRUE);
//    glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    glfwPollEvents ();
//    glfwSetCursorPos (window, 1024/2, 768/2);
//    glClearColor (0.4f, 0.6f, 0.9f, 0.0f);
//    
//    glEnable (GL_DEPTH_TEST);
//    glDepthFunc (GL_LESS);
//    glEnable (GL_CULL_FACE);
//    return 0;
//}
//
//int main () {
//    srand (static_cast <unsigned> (time (0)));
//    if (initGL () == -1)
//        return -1;
//    
//    GLuint programID = LoadShaders ("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
//    GLint MatrixID = glGetUniformLocation (programID, "MVP");
//    
//    /* define all the objects here. */
//    std::vector<Object*> objects;
//    
//    objects.push_back (new Cube (0, -2, 0, 4, true));
//    
//    Cube *kecil = new Cube (0, 7, 0, 1.5, true);
//    objects.push_back ((Object*) kecil);
//    
//    while (glfwGetKey (window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose (window) == 0) {
//        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        
//        glUseProgram (programID);
//        
//        // Compute the MVP matrix from keyboard and mouse input
//        computeMatricesFromInputs ();
//        glm::mat4 ProjectionMatrix = getProjectionMatrix ();
//        glm::mat4 ViewMatrix = getViewMatrix ();
//        glm::mat4 ModelMatrix = glm::mat4 (1.0);
//        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
//        
//        if (!xrot && !yrot)
//            kecil->mengelilingi ();
//        
//        glUniformMatrix4fv (MatrixID, 1, GL_FALSE, &MVP[0][0]);
//    
//        keyboard_callback ();
//        ((Box*) objects[0])->mutar (xrot, yrot, 0);
//        ((Box*) objects[1])->mutar (xrot, yrot, 0);
//        
//        for (int i = 0; i < objects.size (); i++) {
//            // render all objects defined
//            objects[i]->render ();
//        }
//        
//        xrot = yrot = 0;
//        
//        glfwSwapBuffers (window);
//        glfwPollEvents ();
//    }
//    
//    for (int i = 0; i < objects.size (); i++)
//        objects[i]->clean ();
//    glDeleteProgram (programID);
//    
//    // Close OpenGL window and terminate GLFW
//    glfwTerminate ();
//    
//    return 0;
//}
