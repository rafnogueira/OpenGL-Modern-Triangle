//
//  Shader.cpp
//  SDLOpenglTexture
//
//  Created by Rafael Nogueira on 10/07/2018.
//  Copyright © 2018 Rafael Nogueira. All rights reserved.
//

#include "Shader.hpp"


Shader::Shader(void)
{
    
}

Shader::Shader(const char* vertexPath, const char * fragmentPath)
{
    std::string vertexFileData;
    std::string fragmentFileData;
    
    std::ifstream vertexFile;
    std::ifstream fragmentFile;
    
    vertexFile.open(vertexPath);
    fragmentFile.open(fragmentPath);
    
    if(vertexFile.is_open())
    {
        std::stringstream vertexStream;
        vertexStream << vertexFile.rdbuf();
        vertexFileData = vertexStream.str();
        vertexFile.close();
    }
    if(fragmentFile.is_open())
    {
        std::stringstream fragmentStream;
        fragmentStream << fragmentFile.rdbuf();
        fragmentFileData = fragmentStream.str();
        fragmentFile.close();
    }
    
    
    const char* vertexSource = vertexFileData.c_str();
    const char* fragmentSource = fragmentFileData.c_str();
    
    GLuint vertexShader, fragmentShader;
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    
    shaderCompileLog(vertexShader);
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1 , &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    shaderCompileLog(fragmentShader);
    
    IDProgram = glCreateProgram();
    glAttachShader(IDProgram, vertexShader);
    glAttachShader(IDProgram, fragmentShader);
    glLinkProgram(IDProgram);
    programLog(IDProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    
}

Shader::~Shader(void)
{
    
}


void Shader::Use(void)
{
    
    glUseProgram(IDProgram);
    
}

void Shader::setBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(IDProgram, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(IDProgram, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(IDProgram, name.c_str()), value);
}


GLuint Shader::getProgram(void)
{
    return this->IDProgram;
}

void Shader::shaderCompileLog(GLuint &shaderPtr)
{
    int success;
    char info[512];
    glGetShaderiv(shaderPtr, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderPtr , 512, nullptr, info);
        std::cout<<info << std::endl;
        
    }
}

void Shader::programLog(GLuint &ID)
{
    char info[512];
    int success;
    glGetProgramiv(ID , GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, info);
        std::cout << "SHADER PROGRAM LINKING_FAIL: " << info << std::endl;
    }
    
}
