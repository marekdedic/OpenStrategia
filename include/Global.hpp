/**
 * \file Global.hpp
 * \brief File with libraries, dependencies and global variables
 * \author GenaBitu
 **/

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <memory>
#include <iterator>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

class Camera;

extern std::ofstream ERROR; /**< Stream pointing to Errorlog.txt. Used to log errors. */
extern GLFWwindow* WINDOW; /**< Pointer to the main/current/only window */
extern std::shared_ptr<Camera> MAINCAM; /**< Pointer to the main/current/only camera used to render 3D objects */
extern double DELTA; /**< Time (in milliseconds) elapsed during the previous iteration of the main cycle */
extern float SPEED; /**< Game speed multiplier */
extern double PAUSE; /**< If 0, the game runs. If greater than 0, it works like a pause counter in seconds. If -1, the game is paused until "manualy" unpaused (e.g. by pressing the pause key). */
extern glm::dvec2 CURSOR; /**< The position of the cursor represented as a vec2(). Ranges from (0, 0) in the bootom left corner and (width, height) in hte top right corner. */
extern glm::ivec2 SCREENSIZE; /**< Screen size represented as vec2(width, height) */

#endif // GLOBAL_HPP