/**
 * \file RenderableComposite.hpp
 * \brief File with RenderableComposite class
 * \author GenaBitu
 **/

#ifndef RENDERABLECOMPOSITE_HPP
#define RENDERABLECOMPOSITE_HPP
#include "Global.hpp"
#include "Renderable.hpp"

class RenderableComposite : public Renderable
{
public:
    void add(Renderable* child);
    void rem(std::vector<Renderable*>::iterator child);
    void rem(const int child);
protected:
    RenderableComposite();
    virtual ~RenderableComposite();
    std::vector<Renderable*> children;
};

#endif // RENDERABLECOMPOSITE_HPP
