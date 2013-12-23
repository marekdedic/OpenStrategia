/**
 * @file Camera.hpp
 * File with Camera class
 * @author GenaBitu
 **/

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Libs.hpp"

class Camera
{
public:
    glm::mat4 view;
    glm::mat4 projection;
    Camera(float FOV, float aspect);
    void handle();
    ~Camera();
private:
    std::atomic<glm::vec3*> position;
    std::atomic<glm::quat*> orientation;
};

 #endif // CAMERA_HPP
