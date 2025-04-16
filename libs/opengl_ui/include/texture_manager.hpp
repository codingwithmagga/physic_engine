#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>

class TextureManager
{
public:
    TextureManager();

    unsigned int loadTexture(const std::string& filepath);
};

#endif // TEXTURE_MANAGER_H
