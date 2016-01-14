/**
 * \file Renderable.hpp
 * \brief File with Renderable class
 * \author GenaBitu
 **/

#pragma once

#include "Global.hpp"
class Program;

/** \brief Renderable class
 *
 * This abstract class is used to set and retrieve properties of all objects to be rendered on the screen and all renderable containers. Every object to be rendered, 2D or 3D is a child of this class.
 */
class Renderable
{
public:
    std::shared_ptr<glm::mat4> position; /**< Position of the Renderable object represented by a matrix */
    std::shared_ptr<glm::mat4> orientation; /**< Orientation of the Renderable object represented by a matrix */
    /** \brief Renderable event handle
     *
     * Handles user input.
     */
    virtual void handle() = 0;
    /** \brief Update function
     *
     * Must be called on every iteration of the main loop if the Renderable object is to do something.
     */
    virtual void update() = 0;
    /** \brief Renders the object.
     *
     * Must be called on every iteration of the main loop, otherwise the object is not shown/dissappears.
     * \param prg A shader program to use
     */
    virtual void render(std::shared_ptr<Program> prg) const = 0;
    /** \brief Renderable class destructor
     */
protected:
    Renderable(std::shared_ptr<glm::mat4> position, std::shared_ptr<glm::mat4> orientation);
    virtual ~Renderable();
};
