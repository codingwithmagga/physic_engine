#include "shader_program.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

const std::unordered_map<VertexShader, const std::string> ShaderProgram::m_vertexShaderMap = []()
{
    std::unordered_map<VertexShader, const std::string> tempMap;
    tempMap.insert({ VertexShader::BASIC, "shaders/basic_vertex_shader.glsl" });
    tempMap.insert({ VertexShader::OFFSET, "shaders/offset_vertex_shader.glsl" });
    tempMap.insert({ VertexShader::OUTPUT_POS, "shaders/output_pos_vertex_shader.glsl" });
    tempMap.insert({ VertexShader::UPSIDE_DOWN, "shaders/upside_down_vertex_shader.glsl" });
    tempMap.insert({ VertexShader::UPSIDE_DOWN_TEXTURE, "shaders/upside_down_texture_vertex_shader.glsl" });
    return tempMap;
}();

const std::unordered_map<FragmentShader, const std::string> ShaderProgram::m_fragmentShaderMap = []()
{
    std::unordered_map<FragmentShader, const std::string> tempMap;
    tempMap.insert({ FragmentShader::ORANGE, "shaders/orange_fragment_shader.glsl" });
    tempMap.insert({ FragmentShader::YELLOW, "shaders/yellow_fragment_shader.glsl" });
    tempMap.insert({ FragmentShader::MIX, "shaders/mix_fragment_shader.glsl" });
    tempMap.insert({ FragmentShader::POS, "shaders/pos_fragment_shader.glsl" });
    tempMap.insert({ FragmentShader::TEXTURE, "shaders/texture_fragment_shader.glsl" });
    return tempMap;
}();

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode = openFile(vertexPath);
    std::string fragmentCode = openFile(fragmentPath);

    unsigned int vertexShader = compileShader(vertexCode, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER);

    createProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::ShaderProgram(const VertexShader vertexShader, const FragmentShader fragmentShader)
    : ShaderProgram(m_vertexShaderMap.at(vertexShader), m_fragmentShaderMap.at(fragmentShader))
{
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_ID);
}

void ShaderProgram::use() const
{
    glUseProgram(m_ID);
}

void ShaderProgram::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

std::string ShaderProgram::openFile(const std::string& file)
{
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        shaderFile.open(file);

        if (!shaderFile)
        {
            std::cerr << "Unable to open file data.txt\n";
            return std::string();
        }

        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();

        shaderFile.close();

        return shaderStream.str();
    }
    catch (const std::ifstream::failure& e)
    {
        std::cerr << "Exception opening/reading file: " << e.what() << '\n';
        return std::string();
    }
}

unsigned int ShaderProgram::compileShader(const std::string& code, const int shaderType)
{
    unsigned int shaderID;
    int success;
    char infoLog[512];

    shaderID = glCreateShader(shaderType);
    const GLchar* shaderCode = code.c_str();
    glShaderSource(shaderID, 1, &shaderCode, NULL);

    glCompileShader(shaderID);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    return shaderID;
}

void ShaderProgram::createProgram(const unsigned int vertexShader, const unsigned int fragmenShader)
{
    int success;
    char infoLog[512];

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmenShader);
    glLinkProgram(m_ID);

    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}
