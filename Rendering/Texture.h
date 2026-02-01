#pragma once
#include <glad/glad.h>

#include <iostream>
#include <string>

#include <stb_image.h>

class Texture 
{
    GLuint textureID;
public:
    Texture(const std::string& absolutePath);
    ~Texture();
    void bind();
};