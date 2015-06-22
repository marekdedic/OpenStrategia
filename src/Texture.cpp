#include "../Main.hpp"
using namespace std;
using namespace glm;

Texture::Texture() : ID{}, transformation{1}, implementation{}
{
    glGenTextures(1, &ID);
}

Texture::Texture(std::string name) : Texture()
{
    if(!load(name))
    {
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
    }
}

Texture::Texture(const Texture& other) : Texture()
{
    GLint width{}, height{};
    glBindTexture(GL_TEXTURE_2D, other.ID);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    GLubyte* data{new GLubyte[3 * width * height]};
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    delete[] data;
}

Texture& Texture::operator=(const Texture& other)
{
    GLint width{}, height{};
    glBindTexture(GL_TEXTURE_2D, other.ID);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    GLubyte* data{new GLubyte[3 * width * height]};
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    delete[] data;
    return *this;
}

void Texture::use(std::shared_ptr<Program> prg, GLenum texUnit, GLint texUnitNumber, std::string uvMatrix, std::string sampler)
{
    // Send the texture to Graphics card
    glActiveTexture(texUnit);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Send the Texture transformation matrix to GLSL
    GLint loc{glGetUniformLocation(prg->ID, uvMatrix.c_str())};
    glUniformMatrix3fv(loc, 1, GL_FALSE, value_ptr(transformation));

    // Use texture unit
    loc = glGetUniformLocation(prg->ID, sampler.c_str());
    glUniform1i(loc, texUnitNumber);
}

bool Texture::load(std::string name)
{
    string extension = name.substr(name.find_last_of(".") + 1);
    name = "textures/" + name;
    if((extension == "BMP") or (extension == "bmp"))
    {
        implementation.reset(new TextureBMP{});
    }
    else if((extension == "DDS") or (extension == "dds"))
    {
        implementation.reset(new TextureDDS{});
    }
    else
    {
        ERROR << "File " << name <<" is not a valid file format." << endl;
        return false;
    }
    return implementation->load(ID, name);
}

void Texture::hflip()
{
    transformation = mat3(1, 0, 0, 0, -1, 0, 0, 0, 1) * transformation;
}

void Texture::vflip()
{
    transformation = mat3(-1, 0, 0, 0, 1, 0, 0, 0, 1) * transformation;
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}
