#include "../Main.hpp"
using namespace std;
using namespace glm;

bool Texture::TextureBMP::load(GLuint ID, std::string name)
{
    glBindTexture(GL_TEXTURE_2D, ID);
    char* header{new char[54]};
    GLuint dataPos{}, imageSize{}, width{}, height{};
    ifstream file{name, ifstream::binary};
    if(!file.is_open())
    {
        ERROR << "File " << name <<" could not be opened." << endl;
        delete[] header;
        return false;
    }
    file.read(header, 54);
    if(!file.good())
    {
        ERROR << "File " << name << " is not a correct BMP file. No BMP header found." << endl;
        delete[] header;
        return false;
    }
    if(header[0x00] != 'B' || header[0x01] != 'M')
    {
        ERROR << "File " << name << " is not a correct BMP file. Wrong BMP header." << endl;
        delete[] header;
        return false;
    }
    if(header[0x1E] != 0)
    {
        ERROR << "File " << name << " is not a correct BMP file. File is compressed." << endl;
        delete[] header;
        return false;
    }
    if(header[0x1C] != 24)
    {
        ERROR << "File " << name << " is not a correct BMP file. Wrong BitCount. Use 24bpp." << endl;
        delete[] header;
        return false;
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
    char* data{new char[imageSize]};
    file.seekg(dataPos);
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
    return true;
}
