/**
 * \file Text.hpp
 * \brief File with Text class
 * \author GenaBitu
 **/

#ifndef TEXT_HPP
#define TEXT_HPP
#include "Libs.hpp"

/** \brief Text class
 *
 * Displays text on the screen.
 */
class Text : public Image
{
public:
    Text() = delete;
    Text(glm::vec2 inPosition, glm::vec2 inSize, std::shared_ptr<Font> font, std::string s);
    virtual void render(std::shared_ptr<Program> prg) const;
protected:
    Character* head;
};

#endif // TEXT_HPP
