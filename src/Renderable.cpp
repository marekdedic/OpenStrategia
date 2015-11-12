#include "../include/Renderable.hpp"

Renderable::Renderable(std::shared_ptr<glm::mat4> position, std::shared_ptr<glm::mat4> orientation) : position{position}, orientation{orientation} {}

Renderable::~Renderable() {}
