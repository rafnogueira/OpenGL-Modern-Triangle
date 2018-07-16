//
//  Display.hpp
//  SDLOpenglTexture
//
//  Created by Rafael Nogueira on 10/07/2018.
//  Copyright © 2018 Rafael Nogueira. All rights reserved.
//

#ifndef Display_hpp
#define Display_hpp

#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "Shader.hpp"
#include "Texture.hpp"

class Display
{
public:
    Display();
    ~Display();
    void init(const char *title, int width, int height);
    
private:
    GLuint VAO, VBO, EBO;
    GLuint glTexture;
    
    Shader *shader;
    Texture *texTest;

    Texture *texTest2;
    
    int Width, Height;
    bool Running;
    
    GLFWwindow *mWindow;
    
    bool loadOpengl(void);
    void clear(void);
    void mLoop(void);
    void inputManager(GLFWwindow *ptrWindow);
    void update(float delta);
    void render(void);
    
};

#endif /* Display_hpp */
