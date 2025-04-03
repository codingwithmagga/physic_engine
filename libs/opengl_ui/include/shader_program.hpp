#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "gl_include_guard.hpp"

class ShaderProgram
{
public:
    ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
    ~ShaderProgram();

    void use() const;

private:
    std::string openFile(const std::string& file);
    unsigned int compileShader(const std::string& code, const int shaderType);
    void createProgram(const unsigned int vertexShader, const unsigned int fragmenShader);

    unsigned int m_ID;
};

#endif // SHADERPROGRAM_H