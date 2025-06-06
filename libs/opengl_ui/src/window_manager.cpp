﻿#include <iostream>

#include "gl_include_guard.hpp"

#include "shader_program.hpp"
#include "window_manager.hpp"

WindowManager::WindowManager()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }
}

WindowManager::~WindowManager()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}
void WindowManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void WindowManager::processInput()
{

    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }
    if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        m_mixVal += 0.00025f;
        m_mixVal = std::min(1.0f, m_mixVal);
    }
    if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        m_mixVal -= 0.00025f;
        m_mixVal = std::max(0.0f, m_mixVal);
    }
}

void WindowManager::openWindow(const int width, const int height, const std::string& title)
{

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!m_window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        std::cout << "Failed to initialize OpenGL context\n";
        return;
    }
    std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    ShaderProgram shaderProgramTextureMix(VertexShader::UPSIDE_DOWN_TEXTURE, FragmentShader::MIX);
    ShaderProgram shaderProgramPosBasedColor(VertexShader::OUTPUT_POS, FragmentShader::POS);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    float vertices1[] = {
        -0.9f,  -0.5f, 0.0f, 0.0f, 1.0f, // left
        -0.0f,  -0.5f, 0.0f, 1.0f, 1.0f, // right
        -0.45f, 0.5f,  0.0f, 0.5f, 0.0f,
    };
    float vertices2[] = {
        0.0f,  -0.5f, 0.0f, // left
        0.9f,  -0.5f, 0.0f, // right
        0.45f, 0.5f,  0.0f // top
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };
    unsigned int VBOs[2], VAOs[2], EBO;
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex
    // buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep
    // the EBO bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens.
    // Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when
    // it's not directly necessary.
    glBindVertexArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Load and generate texture data
    unsigned int textureWall = m_textureManager.loadTexture("assets/wall.jpg");
    unsigned int textureSmileyFace = m_textureManager.loadTexture("assets/awesomeface.png", true);

    shaderProgramTextureMix.use();
    shaderProgramTextureMix.setInt("texture1", 0);
    shaderProgramTextureMix.setInt("texture2", 1);

    while (!glfwWindowShouldClose(m_window))
    {
        processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgramTextureMix.use();
        shaderProgramTextureMix.setFloat("mixVal", m_mixVal);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureWall);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureSmileyFace);

        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // then we draw the second triangle using the data from the second VAO
        shaderProgramPosBasedColor.use();
        shaderProgramPosBasedColor.setFloat("xOffset", 0.1f);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteBuffers(1, &EBO);
}
