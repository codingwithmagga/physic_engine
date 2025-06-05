#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <string>

#include "texture_manager.hpp"

class GLFWwindow;

class WindowManager
{
public:
    WindowManager();

    ~WindowManager();

    void openWindow(const int width, const int height, const std::string& title);

private:
    void processInput();

    GLFWwindow* m_window = nullptr;
    TextureManager m_textureManager;

    float m_mixVal = 0.2f;
};

#endif // WINDOWMANAGER_H
