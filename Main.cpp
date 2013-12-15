#include "Main.hpp"
using namespace std;
using namespace glm;

std::ofstream error("ErrorLog.txt", fstream::trunc);
bool QUIT = false;
mat4 VIEW;
mat4 PROJECTION = perspective(45.0f, 4.0f / 3.0f, 0.1f, 250.0f);
double DELTA;
int FRAMERATE = 120;
float SPEED = 1.0;
int PAUSE = 0;

int main()
{
    /**< GLFW, GLEW and OpenGL Initialization */
    if(!glfwInit())
    {
        error << "Failed to Initialize GLFW." << endl;
        return -1;
    }
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if(!glfwOpenWindow(1400, 1050, 0, 0, 0, 0, 32, 0, GLFW_FULLSCREEN))
    {
        error << "Failed to open GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
    error << "Failed to initialize GLEW" << endl;
    return -1;
    }
    glfwSetWindowTitle("Tutorial 01");
    glfwEnable(GLFW_STICKY_KEYS);
    glfwEnable(GLFW_MOUSE_CURSOR);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glEnable(GL_CULL_FACE);

    /**< Loading shaders */
    Program* shaders = new Program();
    shaders->AddShader("Vertex.glsl", GL_VERTEX_SHADER);
    shaders->AddShader("Fragment.glsl", GL_FRAGMENT_SHADER);
    shaders->Link();

    /**< Setting up some important variables */
    vec3 cameraPosition = vec3(0, 0, -10);
    quat cameraOrientation = quat(0.9238795325112867, -0.3826834323650897, 0.0, 0.0);
    float cameraMove = 0.1f;
    VIEW = translate(mat4(1.0f), cameraPosition) * mat4_cast(cameraOrientation);

    /**< Reset timer and swap buffers, so that the main loop can start immediatelly */
    glfwSetTime(0);
    glfwSwapBuffers();
    RenderObject3D* objekt = new RenderObject3D();
    while(!QUIT) /**< Main loop */
    {
        /**< Input handling */
        QUIT = (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS);
        if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            cameraPosition += vec3(cameraMove, 0, 0);
        }
        if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            cameraPosition += vec3(-cameraMove, 0, 0);
        }
        if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS)
        {
            cameraPosition += vec3(0, -cameraMove, 0);
        }
        if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            cameraPosition += vec3(0, cameraMove, 0);
        }
        VIEW = translate(mat4(1.0f), cameraPosition) * mat4_cast(cameraOrientation);

        /**< Updating */

        /**< Rendering */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        objekt->render(shaders);

        /**< Timer refresh */
        DELTA = glfwGetTime();
        if (FRAMERATE > 0)
        {
            if(DELTA < (1.0 / FRAMERATE))
            {
                glfwSleep((1.0 / FRAMERATE) - DELTA);
            }
        }
        glfwSetTime(0);
        glfwSwapBuffers();
    }
    glfwTerminate();
}
