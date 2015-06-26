#include "../Main.hpp"
using namespace std;
using namespace glm;

FT_Library Font::library{};

int Font::init()
{
    return FT_Init_FreeType(&library);
}

Font::Font(std::string name)
{
    fileName = "fonts/" + name;
    FT_Error error{FT_New_Face(library, fileName.c_str(), 0, &face)};
    if(error)
    {
        ERROR << "File " << fileName << " is not a correct font file." << endl;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
    }
    error = FT_Set_Pixel_Sizes(face, 0, 50);
    if(error)
    {
        ERROR << "Failed to create font from file:" << fileName << endl;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
    }
}

std::shared_ptr<Image> Font::render(char c)
{
    //shared_ptr<Image> ret = new Image();
    FT_Error error{FT_Load_Char(face, c, FT_LOAD_RENDER)};
    error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
}
