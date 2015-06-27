#include "../Main.hpp"
using namespace std;
using namespace glm;

FT_Library Font::library{};

int Font::init()
{
    return FT_Init_FreeType(&library);
}

Font::Font(std::string name) : face{}, fileName{}
{
    fileName = "fonts/" + name;
    FT_Error error{FT_New_Face(library, fileName.c_str(), 0, &face)};
    if(error)
    {
        ERROR << "File " << fileName << " is not a correct font file." << endl;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
    }
    error = FT_Set_Pixel_Sizes(face, 0, 256);
    if(error)
    {
        ERROR << "Failed to create font from file:" << fileName << endl;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
    }
}

Font::Font(const Font& other) : face{other.face}, fileName{other.fileName} {}
Font& Font::operator=(const Font& other)
{
    face = other.face;
    fileName = other.fileName;
    return *this;
}
