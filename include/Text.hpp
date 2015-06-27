/**
 * \file Text.hpp
 * \brief File with Text class
 * \author GenaBitu
 **/

#ifndef TEXT_HPP
#define TEXT_HPP
#include "Libs.hpp"
#include "Image.hpp"

/** \brief Text class
 *
 * Displays a simple static text on the screen
 */
class Text : public Image
{
public:
    Text() = delete;
    bool load(std::string tex) = delete;
    Text(glm::vec2 inPosition, std::shared_ptr<Font> font, char c, float inAngle = 0);
protected:
};

#endif // TEXT_HPP
