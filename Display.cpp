//
//  Display.cpp
//  OpenGLTexture
//
//  Created by Rafael Nogueira on 10/07/2018.
//  Copyright © 2018 Rafael Nogueira. All rights reserved.
//

#include "Display.hpp"

int main(int argc, char *args[])
{
	Display *game = new Display();
	game->init("Opengl Texture",  800, 600);

	delete game;

    return 0;
}

Display::Display()
{
}

Display::~Display()
{
    this->clear();
}

void Display::init(const char *title, int width, int height)
{

    this->Width = width;
    this->Height = height;
    this->Running = true;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    mWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(mWindow);

    glewExperimental = true;
    glewInit();

    glViewport(0, 0, width, height);

    if (loadOpengl())
    {
        mLoop();
    }
    else {
        exit(0);
    }
}

bool Display::loadOpengl(void)
{

    const char* vertexShaderSrc = "content/shaders/vertexShader.glsl";
    const char* fragmentShaderSrc = "content/shaders/fragmentShader.glsl";

	const char* texture01Src = "content/textures/sample.png";	
	const char* texture02Src = "content/textures/awesomeface.png";
	
    shader = new Shader(vertexShaderSrc, fragmentShaderSrc);

    float vertices[] = {
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    texTest = new Texture();
    texTest->loadTexture(texture01Src);

	texTest2 = new Texture();
	texTest2->loadTexture(texture02Src);
	
    //VAO and VBO and vertices
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //glDisableVertexAttribArray(2);

    //Unbind things after worked with then
    glBindVertexArray(0);

    return true;
}

void Display::clear(void)
{

}

void Display::mLoop(void)
{
    while (!glfwWindowShouldClose(mWindow))
    {
        float dummyDelta = 0.03f;//Delta para calcular o tempo dos frames no futuro TODO
        inputManager(this->mWindow);
        update(dummyDelta);
        render();
        glfwPollEvents();
    }
}

void Display::inputManager(GLFWwindow *ptrWindow)
{
    if(glfwGetKey(ptrWindow, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(ptrWindow, true);
    }
}

void Display::update(float delta){}


void Display::render(void)
{
    //RGB purple 0.5f, 0.0f, 1.0f, 1.0f
    glClearColor(0.5f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    //glPolygonMode(GL_FRONT_FACE, GL_LINE); // denhar apenas os wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	shader->Use();
	
	glUniform1i(glGetUniformLocation(shader->getProgram(), "texKitten"), 0 ) ;

    glUniform1i(glGetUniformLocation(shader->getProgram(), "texPuppy"), 1 );
	
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texTest->getTexture());
    glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texTest2->getTexture());
	
    glBindVertexArray(VAO);
	
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(mWindow);
}
