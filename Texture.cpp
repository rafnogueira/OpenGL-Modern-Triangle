


#include "Texture.hpp"

Texture::Texture()
{

}

Texture::Texture(const char * file_src)
{
    loadTexture(file_src);
}


Texture::~Texture()
{

}

void Texture::loadTexture(const char * file_src)
{
    int width, height, numberChannels;

    
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imageData =  stbi_load(file_src, &width, &height, 0, STBI_rgb);

    //unsigned char* imageData = SOIL_load_image(file_src, &width, &height, 0, SOIL_LOAD_RGB);
    
    if (imageData != nullptr)
    {
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);

        //SOIL_free_image_data(imageData);

        std::cout << "Texture loaded  from stbi_laod with sucess" << std::endl;
    }
    else {
        std::cout << "Texture failed to load" << std::endl;
    }

}

GLuint Texture::getTexture(void)
{
    return texID;
}
