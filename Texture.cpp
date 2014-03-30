#include "Main.hpp"
using namespace std;
using namespace glm;

Texture::Texture(std::string name) : textureID(0)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    name = "textures/" + name;
    ifstream file(name, ifstream::binary);
    if(!file.is_open())
    {
        ERROR << "Failed to load texture: " << name << endl;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        return;
    }
    char* header = new char[124];
    streamsize readsize = 3;
    file.read(header, readsize);
    ERROR << header << "CCCC" << endl;
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}
