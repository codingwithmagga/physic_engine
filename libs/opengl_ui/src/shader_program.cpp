#include "shader_program.hpp"

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

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_ID);
}

void ShaderProgram::use() const
{
    glUseProgram(m_ID);
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
