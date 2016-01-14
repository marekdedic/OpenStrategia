/**
 * \file RenderableComposite.hpp
 * \brief File with RenderableComposite class
 * \author GenaBitu
 **/

#pragma once

#include "Global.hpp"
#include "Renderable.hpp"

class RenderableComposite : public Renderable
{
public:
    void add(Renderable* child);
    void rem(std::vector<Renderable*>::iterator child);
    void rem(const int child);
protected:
    RenderableComposite(std::shared_ptr<glm::mat4> position, std::shared_ptr<glm::mat4> orientation);
    virtual ~RenderableComposite();
    std::vector<Renderable*> children;
};
