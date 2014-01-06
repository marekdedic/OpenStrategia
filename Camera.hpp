/**
 * \file Camera.hpp
 * \brief File with Camera class
 * \author GenaBitu
 **/

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Libs.hpp"

/** \brief Camera class
 *
 * This class completely handles the camera and computes all the matrices based on its properties.
 */
class Camera
{
public:
    std::atomic<glm::mat4*> view; /**< View matrix */
    std::atomic<glm::mat4*> projection; /**< Projection matrix */
    /** \brief Camera class constructor
     *
     * Sets the initial values of the camera as well.
     * \param FOV Field of view used for the camera.
     * \param aspect Aspect ratio of the screen. Usually width / height.
     * \param speed Movement speed.
     * \param position Position represented by a vector.
     * \param orientation Orientation represented by a quaternion.
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
    std::atomic<glm::vec3*> position; /**< Position of the camera represented by a matrix. */
    std::atomic<glm::quat*> orientation; /**< Orientation of the camera represented by a quaternion */
    float speed; /**< Movement speed. */
};

 #endif // CAMERA_HPP
