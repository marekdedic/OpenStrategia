/**
 * \file Camera.hpp
 * \brief File with Camera class
 * \author GenaBitu
 **/

#pragma once

#include "Global.hpp"

/** \brief Camera class
 *
 * This class completely handles the camera and computes all the matrices based on its properties.
 */
class Camera
{
public:
    std::shared_ptr<glm::vec3> position; /**< Position of the camera represented by a matrix */
    std::shared_ptr<glm::mat4> view; /**< View matrix */
    std::shared_ptr<glm::mat4> projection; /**< Projection matrix */
    Camera() = delete;
    /** \brief Camera class copy constructor
     *
     * Copies the texture.
     * \param other Address of the Camera to copy
     */
    Camera(const Camera& other);
    /** \brief Camera class assignment operator
     *
     * Copies the texture.
     * \param other Address of the Camera to copy
     * \return Address of the new Camera
     */
    Camera& operator=(const Camera& other);
    /** \brief Camera class constructor
     *
     * Sets the initial values of the camera.
     * \param FOV Field of view used for the camera (in radians)
     * \param aspect Aspect ratio of the screen. Usually width / height
     * \param speed Movement speed
     * \param position Position represented by a vector
     * \param orientation Orientation represented by a quaternion
     */
    Camera(float FOV, float aspect, float speed, glm::vec3 position, glm::quat orientation);
    /** \brief Camera event handle
     *
     * Handles user input (Cursor and keyboard). Camera is moved when Cursor touches screen edge or user presses arrow key.
     */
    void handle();
    /** \brief Camera class destructor
     *
     * Deletes all dynamically allocated variables.
     */
    ~Camera();
private:
    std::unique_ptr<glm::quat> orientation; /**< Orientation of the camera represented by a quaternion */
    float speed; /**< Movement speed */
};
