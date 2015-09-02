#include "../include/Main.hpp"
using namespace std;
using namespace glm;

Texture::TextureDDS::TextureDDS(Texture* parent) : TextureBridge(parent) {}

bool Texture::TextureDDS::load(std::string name)
{
    fileName = name;
    glBindTexture(GL_TEXTURE_2D, parent->ID);
    ifstream file{fileName, ifstream::binary};
    if(!file.is_open())
    {
        ERROR << "File " << fileName <<" could not be opened." << endl;
        return false;
    }
    DDS_HEADER header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    if(!file.good())
    {
        ERROR << "File " << fileName << " is not a correct DDS file. No DDS header found." << endl;
        return false;
    }
    if((header.magic[0] != 'D') or (header.magic[1] != 'D') or (header.magic[2] != 'S') or (header.magic[3] != ' '))
    {
        ERROR << "File " << fileName << " is not a correct DDS file. Wrong DDS header." << endl;
        return false;
    }
    if((header.structSize != 124) or (header.pixelFormat.structSize != 32))
    {
        ERROR << "File " << fileName << " is not a correct DDS file. Wrong DDS header." << endl;
        return false;
    }
    if((header.width < 1) or (header.height < 1))
    {
        ERROR << "File " << fileName << " is not a correct DDS file. No width or height provided." << endl;
        return false;
    }
    unsigned int bufSize{static_cast<unsigned int>(header.mipmapCount > 1 ? 2 * header.linearSize : header.linearSize)};
    char* data{new char[bufSize]};
    file.read(data, bufSize);
    GLuint format{};
    switch(header.pixelFormat.fourCC)
    {
        case DDS_FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            parent->components = 3;
            break;
        case DDS_FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            parent->components = 4;
            break;
        case DDS_FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            parent->components = 4;
            break;
        case DDS_FOURCC_BC4U:
            format = GL_COMPRESSED_RED_RGTC1_EXT;
            parent->components = 1;
            break;
        case DDS_FOURCC_BC4S:
            format = GL_COMPRESSED_SIGNED_RED_RGTC1_EXT;
            parent->components = 1;
            break;
        case DDS_FOURCC_BC5S:
            format = GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT;
            parent->components = 2;
            break;
        default:
            delete[] data;
            ERROR << "File " << fileName << " is not a correct DDS file. Wrong compression. Use DXT1, DXT3, DXT5, BC4U, BC4S or BC5S." << endl;
            return false;
    }
    GLsizei blockSize{format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ? 8 : 16};
    GLsizei offset{0};
    GLsizei mipSize{};
    for(GLuint level = 0; level < header.mipmapCount; level++)
    {
        mipSize = ((header.width + 3) / 4) * ((header.height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, header.width, header.height, 0, mipSize, data + offset);
        offset += mipSize;
        header.width /= 2;
        header.height /= 2;
        if(header.width < 1)
        {
            header.width = 1;
        }
        if(header.height < 1)
        {
            header.height = 1;
        }
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    if(header.mipmapCount <= 1)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    delete[] data;
    file.close();
    parent->hflip(); // DDS is a DirectX format - V coordinate is flipped
    return true;
}
