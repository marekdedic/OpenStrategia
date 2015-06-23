#include "../Main.hpp"
using namespace std;
using namespace glm;

bool Texture::TextureDDS::load(GLuint ID, std::string name)
{
    glBindTexture(GL_TEXTURE_2D, ID);
    ifstream file{name, ifstream::binary};
    if(!file.is_open())
    {
        ERROR << "File " << name <<" could not be opened." << endl;
        return false;
    }
    char magic[4];
    file.read(magic, 4);
    if(!file.good())
    {
        ERROR << "File " << name << " is not a correct DDS file. No DDS header found." << endl;
        return false;
    }
    if((magic[0x00] != 'D') or (magic[0x01] != 'D') or (magic[0x02] != 'S') or (magic[0x03] != ' '))
    {
        ERROR << "File " << name << " is not a correct DDS file. Wrong DDS header." << endl;
        return false;
    }
    DDS_HEADER header;
    file.read(reinterpret_cast<char*>(&header), 124);
    if(!file.good())
    {
        ERROR << "File " << name << " is not a correct DDS file. No DDS header found." << endl;
        return false;
    }
    if((header.structSize != 124) or (header.pixelFormat.structSize != 32))
    {
        ERROR << "File " << name << " is not a correct DDS file. Wrong DDS header." << endl;
        return false;
    }

    file.close();
    return true;
}
