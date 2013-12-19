/**
 * @file Main.hpp
 * Main header file
 * @author GenaBitu
 **/

#ifndef MAIN_HPP
#define MAIN_HPP

#include "Libs.hpp"

#include "Shader.hpp"
#include "Program.hpp"
#include "RenderObject.hpp"
#include "RenderObject2D.hpp"
#include "RenderObject3D.hpp"

extern std::ofstream error;
extern GLFWwindow* WINDOW;
extern bool QUIT;
extern glm::mat4 VIEW;
extern glm::mat4 PROJECTION;
extern double DELTA;
extern int FRAMERATE;
extern float SPEED;
extern int PAUSE;

#endif // MAIN_HPP
