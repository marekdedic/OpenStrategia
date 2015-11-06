/**
 * \file RenderableCompositeSwitching.hpp
 * \brief File with RenderableCompositeSwitching class
 * \author GenaBitu
 **/

#ifndef RENDERABLECOMPOSITESWITCHING_HPP
#define RENDERABLECOMPOSITESWITCHING_HPP
#include "RenderableComposite.hpp"

class RenderableCompositeSwitching : public RenderableComposite
{
public:
    virtual void render(std::shared_ptr<Program> prg) const override;
    std::vector<Renderable*>::const_iterator active;
protected:
    RenderableCompositeSwitching();
    virtual ~RenderableCompositeSwitching();
};

#endif // RENDERABLECOMPOSITESWITCHING_HPP
