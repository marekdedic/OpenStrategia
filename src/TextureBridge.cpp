#include "../include/Texture.hpp"
using namespace std;
using namespace glm;

Texture::TextureBridge::TextureBridge(Texture* parent) : parent{parent}, fileName{} {}

Texture::TextureBridge::TextureBridge(const TextureBridge& other) : parent{}, fileName{other.fileName} {}

Texture::TextureBridge& Texture::TextureBridge::operator=(const Texture::TextureBridge& other)
{
    fileName = other.fileName;
    return *this;
}

Texture::TextureBridge::~TextureBridge() {}
