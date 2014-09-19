/**
 * \file Main.hpp
 * \brief Main header file
 *
 * Includes all other header files and declares all global-scope variables
 * \author GenaBitu
 **/

#ifndef MAIN_HPP
#define MAIN_HPP

#include "Libs.hpp"

#include "Button.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "Program.hpp"
#include "RenderObject.hpp"
#include "RenderObject2D.hpp"
#include "RenderObject3D.hpp"
#include "Texture.hpp"

extern std::ofstream ERROR; /**< Stream pointing to Errorlog.txt. Used to log errors. */
extern GLFWwindow* WINDOW; /**< Pointer to the main/current/only window. */
extern std::shared_ptr<Camera> MAINCAM; /**< Pointer to the main/current/only camera used to render 3D objects. */
extern double DELTA; /**< Time (in milliseconds) elapsed during the previous iteration of the main cycle. */
extern float SPEED; /**< Game speed multiplier. */
extern int PAUSE; /**< If 0, the game runs. If greater than 0, it works like a pause counter in milliseconds. If -1, the game is paused until "manualy" unpaused (e.g. by pressing the pause key). */
extern double XCURSOR; /**< The X position of the cursor. Ranges from 0 to WIDTH. */
extern double YCURSOR; /**< The Y position of the cursor. Ranges from 0 to HEIGHT. */
extern int WIDTH; /**< Screen width. */
extern int HEIGHT; /**< Screen height. */

#endif // MAIN_HPP
