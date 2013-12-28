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
    std::atomic<glm::mat4*> view;
    std::atomic<glm::mat4*> projection;
    Camera(float FOV, float aspect, float speed, glm::vec3 position, glm::quat orientation);
    void handle();
    ~Camera();
private:
    std::atomic<glm::vec3*> position;
    std::atomic<glm::quat*> orientation;
    float speed;
};

 #endif // CAMERA_HPP
