#include "../include/Camera.hpp"
using namespace std;
using namespace glm;

Camera::Camera(const Camera& other) : position{new vec3{*other.position}}, view{new mat4{*other.view}}, projection{new mat4{*other.projection}}, orientation{new quat{*other.orientation}}, speed{other.speed}
{
}

Camera& Camera::operator=(const Camera& other)
{
    *position= *other.position;
    *view = *other.view;
    *projection = *other.projection;
    *orientation = *other.orientation;
    speed = other.speed;
    return *this;
}

Camera::Camera(float FOV, float aspect, float speed, glm::vec3 position, glm::quat orientation) : position{new vec3{position}}, view{new mat4{translate(mat4{}, position) * mat4_cast(orientation)}}, projection{new mat4{perspective(FOV, aspect, 0.1f, 250.0f)}}, orientation{new quat{orientation}}, speed{speed}
{
}

void Camera::handle()
{
    if((glfwGetKey(WINDOW, GLFW_KEY_LEFT) == GLFW_PRESS) or (CURSOR.x < 2))
    {
        *position += vec3{speed, 0, 0};
    }
    if((glfwGetKey(WINDOW, GLFW_KEY_RIGHT) == GLFW_PRESS) or (CURSOR.x > (SCREENSIZE.x - 2)))
    {
        *position += vec3{-speed, 0, 0};
    }
    if((glfwGetKey(WINDOW, GLFW_KEY_UP) == GLFW_PRESS) or (CURSOR.y > (SCREENSIZE.y - 2)))
    {
        *position += vec3{0, -speed, 0};
    }
    if((glfwGetKey(WINDOW, GLFW_KEY_DOWN) == GLFW_PRESS) or (CURSOR.y < 2))
    {
        *position += vec3{0, speed, 0};
    }
    *view = translate(mat4{}, *position) * mat4_cast(*orientation);
}

Camera::~Camera()
{
    view.reset();
    projection.reset();
    position.reset();
    orientation.reset();
}
