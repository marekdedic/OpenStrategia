#include "../Main.hpp"
using namespace std;
using namespace glm;

Texture::Texture() : ID{}, components{}, transformation{1}, implementation{}
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

Texture::Texture(const Texture& other) : ID{}, components{other.components}, transformation{other.transformation}, implementation{}
{
    glGenTextures(1, &ID);
    GLint maxLevel{}, wrapS{}, wrapT{}, magFilter{}, minFilter{};
    glBindTexture(GL_TEXTURE_2D, other.ID);
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, &maxLevel);
    GLint width[maxLevel + 1], height[maxLevel + 1];
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width[0]);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height[0]);
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &wrapS);
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, &wrapT);
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, &magFilter);
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &minFilter);
    GLubyte* data{new GLubyte[(maxLevel > 0 ? 2 : 1) * components * width[0] * height[0]]};
    int dataPos{0};
    for(GLint level{0}; level <= maxLevel; level++)
    {
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width[level]);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height[level]);
        glGetTexImage(GL_TEXTURE_2D, level, GL_RGB, GL_UNSIGNED_BYTE, &data[dataPos]);
        dataPos += components * width[level] * height[level];
    }
    glBindTexture(GL_TEXTURE_2D, ID);
    dataPos = 0;
    for(GLint level{0}; level <= maxLevel; level++)
    {
        glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, width[level], height[level], 0, GL_RGB, GL_UNSIGNED_BYTE, &data[dataPos]);
        dataPos += components * width[level] * height[level];
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    delete[] data;
    *implementation = *other.implementation;
    implementation->parent = this;
}

Texture& Texture::operator=(const Texture& other)
{
    GLint maxLevel{}, wrapS{}, wrapT{}, magFilter{}, minFilter{};
    glBindTexture(GL_TEXTURE_2D, other.ID);
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, &maxLevel);
    GLint width[maxLevel + 1], height[maxLevel + 1];
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width[0]);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height[0]);
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &wrapS);
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, &wrapT);
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, &magFilter);
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &minFilter);
    GLubyte* data{new GLubyte[(maxLevel > 0 ? 2 : 1) * components * width[0] * height[0]]};
    int dataPos{0};
    for(GLint level{0}; level <= maxLevel; level++)
    {
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width[level]);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height[level]);
        glGetTexImage(GL_TEXTURE_2D, level, GL_RGB, GL_UNSIGNED_BYTE, &data[dataPos]);
        dataPos += components * width[level] * height[level];
    }
    glBindTexture(GL_TEXTURE_2D, ID);
    dataPos = 0;
    for(GLint level{0}; level <= maxLevel; level++)
    {
        glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, width[level], height[level], 0, GL_RGB, GL_UNSIGNED_BYTE, &data[dataPos]);
        dataPos += components * width[level] * height[level];
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    delete[] data;
    *implementation = *other.implementation;
    implementation->parent = this;
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
        implementation.reset(new TextureBMP(this));
    }
    else if((extension == "DDS") or (extension == "dds"))
    {
        implementation.reset(new TextureDDS(this));
    }
    else
    {
        ERROR << "File " << name <<" is not a valid file format." << endl;
        return false;
    }
    return implementation->load(name);
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
