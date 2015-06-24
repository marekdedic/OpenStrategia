#include "../Main.hpp"
using namespace std;
using namespace glm;

Texture::TextureBridge::TextureBridge(Texture* parent) : parent{parent}, fileName{} {}
Texture::TextureBridge::~TextureBridge() {}
