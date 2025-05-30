#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <string>

#include "shader_program.hpp"
#include "texture_manager.hpp"

class WindowManager
{
public:
    WindowManager();

    ~WindowManager();

    void openWindow(const int width, const int height, const std::string& title);

private:
    void processInput();
    unsigned int createVertexShader() const;
    unsigned int createFragmentShaderOrange() const;
    unsigned int createFragmentShaderYellow() const;
    unsigned int createShaderProgram(const unsigned int vertesShader, const unsigned int fragmenShader) const;

    GLFWwindow* m_window = nullptr;
    TextureManager m_textureManager;

    float m_mixVal = 0.2f;
};

#endif // WINDOWMANAGER_H
