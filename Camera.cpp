#include "Main.hpp"
using namespace std;
using namespace glm;

Camera::Camera(float FOV, float aspect)
{
    projection = perspective(FOV, aspect, 0.1f, 250.0f);
}
