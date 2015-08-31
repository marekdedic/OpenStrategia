#include "../Main.hpp"
using namespace std;
using namespace glm;

Texture::TextureBMP::TextureBMP(Texture* parent) : TextureBridge(parent) {}

bool Texture::TextureBMP::load(std::string name)
{
    fileName = name;
    glBindTexture(GL_TEXTURE_2D, parent->ID);
    ifstream file{fileName, ifstream::binary};
    if(!file.is_open())
    {
        ERROR << "File " << fileName <<" could not be opened." << endl;
        return false;
    }
    BMP_HEADER header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    if(!file.good())
    {
        ERROR << "File " << fileName << " is not a correct BMP file. No BMP header found." << endl;
        return false;
    }
    if((header.magic[0] != 'B') or (header.magic[1] != 'M'))
    {
        ERROR << "File " << fileName << " is not a correct BMP file. Wrong BMP signature." << endl;
        return false;
    }
    if(header.numPlanes != 1)
    {
        ERROR << "File " << fileName << " is not a correct BMP file. Wrong number of planes." << endl;
        return false;
    }
    if(header.BPP != 24)
    {
        ERROR << "File " << fileName << " is not a correct BMP file. Wrong BitCount. Use 24bpp." << endl;
        return false;
    }
    if(header.compression != 0)
    {
        ERROR << "File " << fileName << " is not a correct BMP file. File is compressed." << endl;
        return false;
    }
    if(header.imageSize == 0)
    {
        header.imageSize = 3 * header.width * header.height;
    }
    if(header.dataOffset == 0)
    {
        header.dataOffset = 54;
    }
    char* data{new char[header.imageSize]};
    file.seekg(header.dataOffset);
    file.read(data, header.imageSize);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, header.width, header.height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    delete[] data;
    file.close();
    parent->components = 3;
    return true;
}
