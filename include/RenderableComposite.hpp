/**
 * \file RenderableComposite.hpp
 * \brief File with RenderableComposite class
 * \author GenaBitu
 **/

#ifndef RENDERABLECOMPOSITE_HPP
#define RENDERABLECOMPOSITE_HPP
#include "Renderable.hpp"


class RenderableComposite : public Renderable
{
public:
    void add(Renderable* child);
    void rem(std::vector<Renderable*>::const_iterator child);
protected:
    RenderableComposite();
    virtual ~RenderableComposite();
    std::vector<Renderable*> children;
};

#endif // RENDERABLECOMPOSITE_HPP
