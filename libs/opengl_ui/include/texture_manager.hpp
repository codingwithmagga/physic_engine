#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <filesystem>

class TextureManager
{
public:
    TextureManager();

    unsigned int loadTexture(const std::filesystem::path& filepath, const bool flipImage = false);
};

#endif // TEXTURE_MANAGER_H
