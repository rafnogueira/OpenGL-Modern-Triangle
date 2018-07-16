//
//  shaderLoader.hpp
//  SDLOpenglTexture
//  Created by Rafael Nogueira on 10/07/2018.
//  Copyright © 2018 Rafael Nogueira. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    Shader(void);
    Shader(const char* vertexPath, const char * fragmentPath);
    ~Shader(void);

    void Use(void);
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);

    GLuint getProgram(void);

private:
    GLuint IDProgram;
    
    void shaderCompileLog(GLuint &shaderPtr);
    void programLog(GLuint &shaderProgram);
};

#endif /* Shader_hpp */