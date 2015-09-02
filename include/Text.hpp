/**
 * \file Text.hpp
 * \brief File with Text class
 * \author GenaBitu
 **/

#ifndef TEXT_HPP
#define TEXT_HPP
#include "Global.hpp"
#include "Image.hpp"
class Font;
class Character;

/** \brief Text class
 *
 * Displays text on the screen.
 */
class Text : public Image
{
public:
    Text() = delete;
    Text(glm::vec2 inPosition, glm::vec2 inSize, std::shared_ptr<Font> font, std::string s);
    /** \brief Text class copy constructor
     *
     * Copies all the variables and all the buffers.
     * \param other Address of the Text to copy
     */
    Text(const Text& other);
    /** \brief Text class assignment operator
     *
     * Copies all the variables and all the buffers.
     * \param other Address of the Text to copy
     * \return Address of the new Text
     */
    Text& operator=(const Text& other);
    virtual void update() override;
    virtual void render(std::shared_ptr<Program> prg) const;
protected:
    Character* head;
};

#endif // TEXT_HPP
