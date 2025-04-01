#include <gl.h>

#include <GLFW/glfw3.h>

#include <string>

class WindowManager
{
public:
    WindowManager();

    ~WindowManager()
    {
        if (m_window)
        {
            glfwDestroyWindow(m_window);
            glfwTerminate();
        }
    }

    void openWindow(const int width, const int height, const std::string& title);

private:
    void processInput();
    unsigned int createVertexShader() const;
    unsigned int createFragmentShader() const;
    unsigned int createShaderProgram(const unsigned int vertesShader, const unsigned int fragmenShader) const;

    GLFWwindow* m_window = nullptr;
};