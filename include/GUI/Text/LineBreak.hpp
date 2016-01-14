/**
 * \file LineBreak.hpp
 * \brief File with LineBreak class
 * \author GenaBitu
 **/

#pragma once

#include "../../Global.hpp"
#include "Character.hpp"

/** \brief LineBreak class
 *
 * A character used to start a new line of text.
 */
class LineBreak : public Character
{
public:
    LineBreak() = delete;
    LineBreak(glm::vec2 inPosition, std::shared_ptr<Font> font, char c, Character* previous, float inAngle) = delete;
    LineBreak(glm::vec2 inPosition, std::shared_ptr<Font> font, Character* previous);
    virtual void update() override;
    virtual void render(std::shared_ptr<Program> prg) const override;
};
