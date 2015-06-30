#include "../Main.hpp"
using namespace std;
using namespace glm;

Character::Character(glm::vec2 inPosition, std::shared_ptr<Font> font, char c, float inAngle): Image(inPosition, vec2{1, 1}, inAngle), glyphIndex{FT_Get_Char_Index(font->face, c)}, next{}
{
    FT_Error error{FT_Load_Glyph(font->face, glyphIndex, FT_LOAD_DEFAULT)};
    error += FT_Render_Glyph(font->face->glyph, FT_RENDER_MODE_NORMAL);
    if(error or (font->face->glyph->bitmap.pixel_mode != FT_PIXEL_MODE_GRAY))
    {
        ERROR << "Failed to render text." << endl;
        glfwSetWindowShouldClose(WINDOW, GL_TRUE);
    }
    imageSize.x = font->face->glyph->bitmap.width;
    imageSize.y = font->face->glyph->bitmap.rows;
    update();
    unsigned int bufSize{static_cast<unsigned int>(4 * imageSize.x * imageSize.y)};
    GLubyte* data = new GLubyte[bufSize];
    for(unsigned int i{0}; i < (imageSize.x * imageSize.y); i++)
    {
        data[4 * i] = font->face->glyph->bitmap.buffer[i];
        data[(4 * i) + 1] = font->face->glyph->bitmap.buffer[i];
        data[(4 * i) + 2] = font->face->glyph->bitmap.buffer[i];
        data[(4 * i) + 3] = font->face->glyph->bitmap.buffer[i];
    }
    glBindTexture(GL_TEXTURE_2D, texture->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSize.x, imageSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    texture->hflip();
    texture->components = 4;
}

void Character::render(std::shared_ptr<Program> prg) const
{
    Image::render(prg);
    if(next != nullptr)
    {
        next->render(prg);
    }
}
