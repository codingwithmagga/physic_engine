#include "texture_manager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Necessary for GL files
#include "shader_program.hpp"

TextureManager::TextureManager()
{
}

unsigned int TextureManager::loadTexture(const std::filesystem::path& filepath, const bool flipImage)
{
    stbi_set_flip_vertically_on_load(flipImage);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int image_width, image_height, nrChannels;

    unsigned char* data = stbi_load(filepath.string().c_str(), &image_width, &image_height, &nrChannels, 0);
    if (data)
    {
        if (filepath.extension() == ".png")
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture;
}
