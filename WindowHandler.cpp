#include "WindowHandler.h"
#include "InputHandler.h"
#include "Renderer.h"

WindowHandler &WindowHandler::getInstance() {
    static WindowHandler instance;
    return instance;
}

WindowHandler::WindowHandler()
    : window(nullptr)
    , targetTime(0.0)
    , currentTime(0.0)
    , previousTime(0.0)
    , frameTime(0.0)
{
}

void WindowHandler::ErrorCallback(int error, const char *description)
{
    TraceLog(LOG_ERROR, description);
}

void WindowHandler::initWindowAndDevice(int screenWidth, int screenHeight, const char *title, int targetFPS) {
    this->initWindow(screenWidth, screenHeight, title);
    this->initGraphicsDevice(screenWidth, screenHeight);
    this->initGraphicsDevice(screenWidth, screenHeight);
    this->setTargetFPS(targetFPS);
}

void WindowHandler::initWindow(int screenWidth, int screenHeight, const char *title)
{
    glfwSetErrorCallback(WindowHandler::ErrorCallback);

    if (!glfwInit()) TraceLog(LOG_WARNING, "GLFW3: Can not initialize GLFW");
    else TraceLog(LOG_INFO, "GLFW3: GLFW initialized successfully");

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    this->window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);

    if (!window) glfwTerminate();
    else TraceLog(LOG_INFO, "GLFW3: Window created successfully");

    glfwSetWindowPos(window, 200, 200);

    auto func = [](GLFWwindow *w, int key, int scancode, int action, int mods) {
        InputHandler::getInstance().KeyCallback(w, key, scancode, action, mods);
    };
    glfwSetKeyCallback(window, func);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void WindowHandler::closeWindow(void)
{
    Renderer::Close();
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void WindowHandler::setTargetFPS(int fps)
{
    if (fps < 1) this->targetTime = 0.0;
    else this->targetTime = 1.0 / (double)fps;
}

void WindowHandler::syncFrame(void)
{
    // Frame time control system
    this->currentTime = glfwGetTime();
    this->frameTime = this->currentTime - this->previousTime;
    this->previousTime = this->currentTime;

    // Wait for some milliseconds...
    if (this->frameTime < this->targetTime)
    {
        double prevTime = glfwGetTime();
        double nextTime = 0.0;

        // Busy wait loop
        while ((nextTime - prevTime) < (this->targetTime - this->frameTime)) nextTime = glfwGetTime();

        this->currentTime = glfwGetTime();
        double extraTime = this->currentTime - this->previousTime;
        this->previousTime = currentTime;

        this->frameTime += extraTime;
    }
}

void WindowHandler::initGraphicsDevice(int width, int height)
{
    // Load OpenGL 3.3 supported extensions
    rlLoadExtensions(glfwGetProcAddress);

    // Initialize OpenGL context (states and resources)
    rlglInit(width, height);

    // Initialize viewport and internal projection/modelview matrices
    rlViewport(0, 0, width, height);
    rlMatrixMode(RL_PROJECTION);                        // Switch to PROJECTION matrix
    rlLoadIdentity();                                   // Reset current matrix (PROJECTION)
    rlOrtho(0, width, height, 0, 0.0f, 1.0f);           // Orthographic projection with top-left corner at (0,0)
    rlMatrixMode(RL_MODELVIEW);                         // Switch back to MODELVIEW matrix
    rlLoadIdentity();                                   // Reset current matrix (MODELVIEW)

    rlClearColor(0, 0, 0, 255);                         // Define clear color (BLACK)
    rlEnableDepthTest();                                // Enable DEPTH_TEST for 3D
}

bool WindowHandler::shouldClose() { return glfwWindowShouldClose(this->window); }

GLFWwindow* WindowHandler::getWindow() { return this->window; }

void WindowHandler::beginDrawing() {
    Renderer::ClearBuffers();
}

void WindowHandler::endDrawing() {
    Renderer::Draw();
    glfwSwapBuffers(this->window);
    InputHandler::getInstance().PollInputEvents();
    this->syncFrame();
}
