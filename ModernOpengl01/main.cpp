
extern "C"
{
    
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
}
#include <iostream>


using namespace  std;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


GLfloat triangle_vertices[] = {
    0.0,  0.8,
    -0.8, -0.8,
    0.8, -0.8
};

//Global variable to store GLSL  ( combination of Fragment shader and fragment shader);
GLuint program;


//Nos mencionamos que passaríamos cada vértice do triângulo para o vertex shader, usando o atributo coord2d. Aqui é como declaremos ele em nosso código C.
GLint attribute_coord2d;


void loadShaders()
{
    const char *vertexShaderSrc =
#ifdef GL_ES_VERSION_2_0
    "#version 100\n"  // OpenGL ES 2.0
#else
    "#version 120\n"  // OpenGL 2.1
#endif
    "attribute vec2 coord2d;                  "
    "void main(void) {                        "
    "  gl_Position = vec4(coord2d, 0.0, 1.0); "
    "}";
    
    const char *fragmentShaderSrc =
    "#version 120           \n"
    "void main(void) {        "
    "  gl_FragColor[0] = 0.0; "
    "  gl_FragColor[1] = 0.0; "
    "  gl_FragColor[2] = 1.0; "
    "}";
    

    
    
    GLint compile_ok = GL_FALSE;
    GLint link_ok = GL_FALSE;
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader , 1 , &vertexShaderSrc ,nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compile_ok);
    if (0 == compile_ok)
        cout<<"Vertex Shader compilado com erros!" ;
       

    GLuint fragmentShader  = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader , 1, &fragmentShaderSrc ,nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compile_ok);
    if(!compile_ok)
        cout<<"Erro ao compilar fragment shader!"<<endl;
    
    // Fragment shader and Vertex shaders compiled  link into program GLSL
    
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok); // its link ok ?
    if(!link_ok)
        cout<<"erro linkin the glsl";
 
    /// Create Atribbutes
    const char *attributeName = "coord2d";
    attribute_coord2d  = glGetAttribLocation(program, attributeName);
    if(attribute_coord2d == -1)
        cout<< "Error finding the atribute in program";
    
    
}

int main(void)
{
    glfwInit();
    GLFWwindow* window;
    
    window = glfwCreateWindow(800, 600, "Simple example", NULL, NULL);
    
    glfwSetWindowSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    
    GLenum glew_status =  glewInit();
    if(glew_status != GLEW_OK)
    {
        std::cout<< "Error in GLEW " << std::endl;
    }
    std::cout<< " Version "<<glGetString(GL_VERSION);
    
    loadShaders();
    
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.7, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glEnableVertexAttribArray(attribute_coord2d);
        GLfloat triangle_vertices[] = {
            0.0,  0.8,
            -0.8, -0.8,
            0.8, -0.8,
        };
        
        glVertexAttribPointer(
                              attribute_coord2d, // atributo
                              2,                 // numero de elementos por vértice, que é (x,y)
                              GL_FLOAT,          // o tipo de cada elemento
                              GL_FALSE,          // Como os nossos valores são falsos.
                              0,                 // sem informação extra em cada posição.
                              triangle_vertices  // pontos para a array do C.
                              );
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(attribute_coord2d);
        
        // old opengl
//        glViewport(7, 0, 800, 600);
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        glOrtho(-100, 100, -100, 100, 0.0, 10.0);
//
//        glMatrixMode(GL_MODELVIEW);
//
//        glBegin(GL_TRIANGLES);
//        glVertex3f(-50, -50, 0);
//        glVertex3f(0, 100, 0);
//        glVertex3f(50, -50,0);
//        glEnd();
//
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

