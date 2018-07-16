#pragma once

#include "stb_image.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <SOIL/SOIL.h>

class Texture
{
public:
    Texture();
    Texture(const char * file_src);
    ~Texture();
    void loadTexture(const char *file_src);
    
    GLuint getTexture(void);
private:
 
    GLuint texID;
};

