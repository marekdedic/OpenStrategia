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
    file.close();
    return true;
}
