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
    file.read(header, 4);
    if(strncmp(header, "DDS ", 4) != 0)
    {
        ERROR << "Not a DDS texture: " << name << endl;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        return;
    }
    file.read(header, 124);
    GLuint height = *(unsigned int*)&(header[8]);
    GLuint width = *(unsigned int*)&(header[12]);
    GLuint linearSize = *(unsigned int*)&(header[16]);
    GLuint mipMapCount = *(unsigned int*)&(header[24]);
    GLuint fourCC = *(unsigned int*)&(header[80]);
    unsigned char* buffer;
    GLuint bufsize;
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = new unsigned char[bufsize];
    file.read(reinterpret_cast<char*>(buffer), bufsize);
    GLuint format;
    switch(fourCC)
    {
        case 0x31545844:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case 0x33545844:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case 0x35545844:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            ERROR << "Not a DXT texture: " << name << endl;
            glfwSetWindowShouldClose(WINDOW, GL_TRUE);
            delete[] buffer;
            return;
    }
    GLuint blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    GLuint offset = 0;
    for (GLuint level = 0; level < mipMapCount; level++)
    {
        GLuint psize = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, psize, buffer + offset);
        offset += psize;
        width /= 2;
        height /= 2;
        if(width < 1) {width = 1;}
        if(height < 1) {height = 1;}
    }
    delete[] buffer;
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}
