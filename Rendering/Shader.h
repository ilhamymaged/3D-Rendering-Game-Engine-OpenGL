#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <mat4x4.hpp> 
#include <ext/matrix_transform.hpp> 
#include <ext/matrix_clip_space.hpp> 

class Shader
{
public:
    Shader(const std::string& name, const char* geomertyName = nullptr);
    ~Shader();

    void use();
    void setMat4(const glm::mat4& value, const std::string& name);
    void setVec3(const glm::vec3& value, const std::string& name);
    void setArrayVec3(const std::vector<glm::vec3>& value, const std::string& name);
    void setArrayMat4(const std::vector<glm::mat4>& value, const std::string& name);
    void setBool(bool value, const std::string& name);
    void setInt(int value, const std::string& name);
    void setFloat(float value, const std::string& name);
    void setFloatArray(const std::string& name, const float* data, int count);
    void setVec2(const std::string& name, const glm::vec2& value);

private:
    GLuint id;
    std::unordered_map<std::string, GLint> uniformLocations;

    GLint getUniformLocation(const std::string& name);
    std::string readConfigFile(const std::string& filename);
};