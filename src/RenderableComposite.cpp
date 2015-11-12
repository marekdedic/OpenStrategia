#include "../include/RenderableComposite.hpp"

void RenderableComposite::add(Renderable* child)
{
    children.push_back(child);
}

void RenderableComposite::rem(std::vector<Renderable*>::iterator child)
{
    children.erase(child);
}

void RenderableComposite::rem(const int child)
{
    children.erase(children.begin() + child);
}

RenderableComposite::RenderableComposite(std::shared_ptr<glm::mat4> position, std::shared_ptr<glm::mat4> orientation) : Renderable{position, orientation}, children{} {}

RenderableComposite::~RenderableComposite()
{
    children.erase(children.begin(), children.end());
}
