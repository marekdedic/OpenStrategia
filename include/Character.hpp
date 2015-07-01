/**
 * \file Character.hpp
 * \brief File with Character class
 * \author GenaBitu
 **/

#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "Libs.hpp"
#include "Image.hpp"
#include "Font.hpp"

/** \brief Character class
 *
 * Displays one character on the screen.
 */
class Character : public Image
{
public:
    Character* previous;
    Character* next;
    glm::vec2 origin;
    FT_Glyph_Metrics metrics;
    GLfloat kerning;
    Character() = delete;
    bool load(std::string tex) = delete;
    Character(glm::vec2 inPosition, std::shared_ptr<Font> font, char c, Character* previous, float inAngle = 0);
    virtual void render(std::shared_ptr<Program> prg) const override;
    void position();
private:
    FT_UInt glyphIndex;
};

#endif // TEXT_HPP
