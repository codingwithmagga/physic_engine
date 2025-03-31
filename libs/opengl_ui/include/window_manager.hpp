#include <gl.h>

#include <GLFW/glfw3.h>

#include <string>

class WindowManager
{
public:
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
    GLFWwindow* m_window = nullptr;
};