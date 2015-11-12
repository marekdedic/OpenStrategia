/**
 * \file RenderableCompositeSwitching.hpp
 * \brief File with RenderableCompositeSwitching class
 * \author GenaBitu
 **/

#ifndef RENDERABLECOMPOSITESWITCHING_HPP
#define RENDERABLECOMPOSITESWITCHING_HPP
#include "Global.hpp"
#include "RenderableComposite.hpp"

class RenderableCompositeSwitching : public RenderableComposite
{
public:
    virtual void render(std::shared_ptr<Program> prg) const override;
    int active;
protected:
    RenderableCompositeSwitching(std::shared_ptr<glm::mat4> position, std::shared_ptr<glm::mat4> orientation);
    virtual ~RenderableCompositeSwitching();
};

#endif // RENDERABLECOMPOSITESWITCHING_HPP
