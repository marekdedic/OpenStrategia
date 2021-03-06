#include "Main.hpp"
using namespace std;
using namespace glm;

std::ofstream ERROR{"ErrorLog.txt", fstream::trunc};
GLFWwindow* WINDOW{};
std::shared_ptr<Camera> MAINCAM{new Camera{3.1415926535 / 4, 4.0 / 3.0, 0.1, vec3{0, 0, -10}, quat{0.9238795325112867, -0.3826834323650897, 0, 0}}};
double DELTA{};
float SPEED{1};
double PAUSE{0};
glm::dvec2 CURSOR{};
glm::ivec2 SCREENSIZE{};

int main()
{
    // GLFW, GLEW and OpenGL Initialization
    if(glfwInit() != GL_TRUE)
    {
        ERROR << "Failed to Initialize GLFW." << endl;
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWmonitor* monitor{glfwGetPrimaryMonitor()};
    WINDOW = glfwCreateWindow(1400, 1050, "OpenStrategia", monitor, nullptr);
    glfwMakeContextCurrent(WINDOW);
    if(!WINDOW)
    {
        ERROR << "Failed to open GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwSwapInterval(1);
    glfwSetInputMode(WINDOW, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(WINDOW, GLFW_CURSOR, GL_TRUE);
    glfwGetWindowSize(WINDOW, &SCREENSIZE.x, &SCREENSIZE.y);

    glewExperimental = GL_TRUE;
    GLenum GLEWerror{glewInit()};
    if(GLEWerror != GLEW_OK)
    {
        ERROR << "Failed to initialize GLEW: " << glewGetErrorString(GLEWerror) << endl;
        glfwTerminate();
        return -1;
    }
    glGetError();                           // Flush error - glewInit() may set errorflag even if everything is OK
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Loading shaders
    std::shared_ptr<Program> shaders3D{new Program};
    shaders3D->addShader("phong.vertex.glsl", GL_VERTEX_SHADER);
    shaders3D->addShader("phong.fragment.glsl", GL_FRAGMENT_SHADER);
    std::shared_ptr<Program> shaders2D{new Program};
    shaders2D->addShader("2D.vertex.glsl", GL_VERTEX_SHADER);
    shaders2D->addShader("2D.fragment.glsl", GL_FRAGMENT_SHADER);
    if(glfwWindowShouldClose(WINDOW)) {return -1;}
    shaders3D->link();
    shaders2D->link();

    // Reset timer and swap buffers, so that the main loop can start immediatelly
    glfwSetTime(0);
    glfwSwapBuffers(WINDOW);
    glfwPollEvents();

                                                                        vector<GLfloat> vData{
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
	};
                                                                        vector<GLfloat> vData2{
		-0.5f,-1.0f, 0.0f,
		 1.0f,-1.0f, 0.0f,
		 1.0f, 1.0f, 0.0f,
	};
                                                                        vector<GLuint> iData{0,1,2,1,3,2,4,7,5,6,4,5,1,5,7,1,7,3,2,4,0,6,0,4,3,7,4,3,4,2,1,5,6,1,6,0};
                                                                        vector<GLuint> iData2{0,1,2};
                                                                        //RenderObject3D* objekt{new RenderObject3D{&vData, &iData}};
                                                                        RenderObject3D* objekt2{new RenderObject3D{"tank.obj"}};
                                                                        Slider* objekt3{new Slider{100, 50, vec2{50, 50}, vec2{300, 40}, vec2{40, 40}, vec2{30, 40}, "slider-BG.bmp", "slider-slider.bmp", "slider-left.bmp", "slider-leftP.bmp"}};
    while(!glfwWindowShouldClose(WINDOW)) // Main loop
    {
        // Rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                                                        //objekt->render(shaders, MAINCAM);
                                                                        objekt2->render(shaders3D, MAINCAM);
                                                                        objekt3->render(shaders2D);

        // Input handling
        glfwGetCursorPos(WINDOW, &CURSOR.x, &CURSOR.y);
        CURSOR.y = SCREENSIZE.y - CURSOR.y;
        if(glfwGetKey(WINDOW, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(WINDOW, GL_TRUE);
        }
        if((glfwGetKey(WINDOW, GLFW_KEY_LEFT) == GLFW_PRESS) or (glfwGetKey(WINDOW, GLFW_KEY_RIGHT) == GLFW_PRESS) or (glfwGetKey(WINDOW, GLFW_KEY_UP) == GLFW_PRESS) or (glfwGetKey(WINDOW, GLFW_KEY_DOWN) == GLFW_PRESS) or (CURSOR.x < 2) or (CURSOR.y < 2) or (CURSOR.x > (SCREENSIZE.x - 2)) or (CURSOR.y > (SCREENSIZE.y - 2)))
        {
            thread t(&Camera::handle, MAINCAM);
            t.detach();
        }
                                                                        objekt3->handle();

        // Updating
                                                                        objekt3->update();

        // Timer restart
        DELTA = glfwGetTime();
        glfwSetTime(0);
        glfwSwapBuffers(WINDOW);
        glfwPollEvents();
    }
    //delete objekt;
    delete objekt2;
    delete objekt3;
    shaders3D.reset();
    shaders2D.reset();
    MAINCAM.reset();
    glfwDestroyWindow(WINDOW);
    glfwTerminate();
}
