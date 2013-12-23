#include "Main.hpp"
using namespace std;
using namespace glm;

Camera::Camera(float FOV, float aspect, float speed, vec3 position, quat orientation) : view(new mat4(translate(mat4(1.0f), position) * mat4_cast(orientation))), projection(new mat4(perspective(FOV, aspect, 0.1f, 250.0f))), position(new vec3(position)), orientation(new quat(orientation)), speed(speed)
{
}

void Camera::handle()
{
    if(glfwGetKey(WINDOW, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        *position += vec3(speed, 0, 0);
    }
    if(glfwGetKey(WINDOW, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        *position += vec3(-speed, 0, 0);
    }
    if(glfwGetKey(WINDOW, GLFW_KEY_UP) == GLFW_PRESS)
    {
        *position += vec3(0, -speed, 0);
    }
    if(glfwGetKey(WINDOW, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        *position += vec3(0, speed, 0);
    }
    *view = translate(mat4(1.0f), *position) * mat4_cast(*orientation);
}

Camera::~Camera()
{
    delete view;
    delete projection;
    delete position;
    delete orientation;
}
