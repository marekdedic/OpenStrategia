/**
 * \file RenderableComposite.hpp
 * \brief File with RenderableCompositeParallel class
 * \author GenaBitu
 **/

#ifndef RENDERABLECOMPOSITEPARALLEL_HPP
#define RENDERABLECOMPOSITEPARALLEL_HPP
#include "RenderableComposite.hpp"

class RenderableCompositeParallel : public RenderableComposite
{
public:
    virtual void update() override;
protected:
    RenderableCompositeParallel();
    virtual ~RenderableCompositeParallel();
};

#endif // RENDERABLECOMPOSITEPARALLEL_HPP
