#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <unordered_map>

#include "gl_include_guard.hpp"

enum class VertexShader
{
    BASIC,
    OFFSET,
    OUTPUT_POS,
    UPSIDE_DOWN,
    UPSIDE_DOWN_TEXTURE
};

enum class FragmentShader
{
    ORANGE,
    YELLOW,
    MIX,
    POS,
    TEXTURE
};

class ShaderProgram
{
public:
    ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
    ShaderProgram(const VertexShader vertexShader, const FragmentShader fragmentShader);
    ~ShaderProgram();

    void use() const;

    void setInt(const std::string& name, int value) const;

    void setFloat(const std::string& name, float value) const;

private:
    std::string openFile(const std::string& file);
    unsigned int compileShader(const std::string& code, const int shaderType);
    void createProgram(const unsigned int vertexShader, const unsigned int fragmenShader);

    static const std::unordered_map<VertexShader, const std::string> m_vertexShaderMap;
    static const std::unordered_map<FragmentShader, const std::string> m_fragmentShaderMap;

    unsigned int m_ID;
};

#endif // SHADERPROGRAM_H
