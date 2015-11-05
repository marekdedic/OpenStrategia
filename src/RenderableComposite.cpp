#include "../include/RenderableComposite.hpp"

void RenderableComposite::add(Renderable* child)
{
    children.push_back(child);
}

void RenderableComposite::rem(std::vector<Renderable*>::const_iterator child)
{
    children.erase(child);
}

RenderableComposite::RenderableComposite() : Renderable{}, children{} {}

RenderableComposite::~RenderableComposite()
{
    children.erase(children.begin(), children.end());
}
