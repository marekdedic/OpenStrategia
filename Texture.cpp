#include "Main.hpp"
using namespace std;
using namespace glm;

Texture::Texture(std::string name) : textureID(0)
{
    name = "textures/" + name;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    char* header = new char[54];
    GLuint dataPos, imageSize, width, height;
    ifstream file(name, ifstream::binary);
    if(!file.is_open())
    {
        ERROR << "File " << name <<" could not be opened." << endl;
        delete[] header;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        return;
    }
    file.read(header, 54);
    if(!file.good())
    {
        ERROR << "File " << name << " is not a correct BMP file. No BMP header found." << endl;
        delete[] header;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        return;
    }
    if(header[0x00] != 'B' || header[0x01] != 'M')
    {
        ERROR << "File " << name << " is not a correct BMP file. Wrong BMP header." << endl;
        delete[] header;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        return;
    }
    if(header[0x1E] != 0)
    {
        ERROR << "File " << name << " is not a correct BMP file. File is compressed." << endl;
        delete[] header;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        return;
    }
    if(header[0x1C] != 24)
    {
        ERROR << "File " << name << " is not a correct BMP file. Wrong BitCount. Use 24bpp." << endl;
        delete[] header;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        return;
    }
    dataPos = *reinterpret_cast<int*>(&header[0x0A]);
    imageSize = *reinterpret_cast<int*>(&header[0x22]);
    width = *reinterpret_cast<int*>(&header[0x12]);
    height = *reinterpret_cast<int*>(&header[0x16]);
    if(imageSize == 0)
    {
        imageSize = 3 * width * height;
    }
    if(dataPos == 0)
    {
        dataPos = 54;
    }
    char* data = new char[imageSize];
    file.read(data, imageSize);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    delete[] header;
    delete[] data;
    file.close();
}

Texture::Texture(const Texture& other) : textureID(0)
{
    GLint textureWidth = 0, textureHeight = 0;
    GLuint framebufferID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, other.textureID);
    glGenFramebuffers(1, &framebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, other.textureID, 0);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
    ERROR << "zacatek" << glGetError() << endl;
    glBlitFramebuffer(0, 0, textureWidth, textureHeight, 0, 0, textureWidth, textureHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    ERROR << "konec" << glGetError() << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Texture& Texture::operator=(const Texture& other)
{
    if(this != &other)
    {
        textureID = 0;



    }
    return *this;
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}
