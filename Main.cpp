#include "Main.hpp"
using namespace std;
using namespace glm;

std::ofstream error("ErrorLog.txt", fstream::trunc);
GLFWwindow* WINDOW;
Camera* mainCam = new Camera(45, 4.0 / 3.0, 0.1, vec3(0, 0, -10), quat(0.9238795325112867, -0.3826834323650897, 0, 0));
double DELTA;
int FRAMERATE = 120;
float SPEED = 1.0;
int PAUSE = 0;

int main()
{
    /**< GLFW, GLEW and OpenGL Initialization */
    if(glfwInit() != GL_TRUE)
    {
        error << "Failed to Initialize GLFW." << endl;
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    WINDOW = glfwCreateWindow(1400, 1050, "OpenStrategia", monitor, nullptr);
    glfwMakeContextCurrent(WINDOW);
    if(!WINDOW)
    {
        error << "Failed to open GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glewExperimental = GL_TRUE;
    GLenum GLEWerror = glewInit();
    if(GLEWerror != GLEW_OK)
    {
    error << "Failed to initialize GLEW: " << glewGetErrorString(GLEWerror) << endl;
    glfwTerminate();
    return -1;
    }
    glfwSwapInterval(1);
    glfwSetInputMode(WINDOW, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(WINDOW, GLFW_CURSOR, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    /**< Loading shaders */
    Program* shaders = new Program;
    shaders->AddShader("Vertex.glsl", GL_VERTEX_SHADER);
    shaders->AddShader("Fragment.glsl", GL_FRAGMENT_SHADER);
    shaders->Link();

    /**< Setting up some important variables */

    /**< Reset timer and swap buffers, so that the main loop can start immediatelly */
    glfwSetTime(0);
    glfwSwapBuffers(WINDOW);
    glfwPollEvents();
                                                                        vector<GLfloat> vData = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
	};
                                                                        vector<GLuint> iData = {0,1,2,1,3,2,4,7,5,6,4,5,1,5,7,1,7,3,2,4,0,6,0,4,3,7,4,3,4,2,1,5,6,1,6,0};
                                                                        RenderObject3D* objekt = new RenderObject3D(&vData, &iData);
                                                                        //RenderObject2D* objekt2 = new RenderObject2D;

    while(glfwWindowShouldClose(WINDOW) == GL_FALSE) /**< Main loop */
    {
        /**< Rendering */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                                                        objekt->render(shaders, mainCam);
                                                                        //objekt2->render(shaders);

        /**< Input handling */
        if(glfwGetKey(WINDOW, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        }
        thread t(&Camera::handle, mainCam);
        t.detach();

        /**< Updating */

        /**< Timer refresh */
        DELTA = glfwGetTime();
        glfwSetTime(0);
        glfwSwapBuffers(WINDOW);
        glfwPollEvents();
    }
    delete objekt;
    //delete objekt2;
    delete shaders;
    delete mainCam;
    glfwTerminate();
}
