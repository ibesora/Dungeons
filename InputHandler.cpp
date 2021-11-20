#include "InputHandler.h"
#include "WindowHandler.h"
#include <GLFW/glfw3.h>

InputHandler &InputHandler::getInstance() {
    static InputHandler instance;
    return instance;
}

InputHandler::InputHandler()
    : previousKeyState{0}
    , currentKeyState{0}
{
}

void InputHandler::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else this->currentKeyState[key] = action;
}

bool InputHandler::isKeyDown(int key)
{
    return glfwGetKey(WindowHandler::getInstance().getWindow(), key);
}

bool InputHandler::isKeyPressed(int key)
{
    if ((this->currentKeyState[key] != this->previousKeyState[key]) && (this->currentKeyState[key] == 1)) return true;
    else return false;
}

void InputHandler::PollInputEvents(void)
{
    for (int i = 0; i < 512; i++) this->previousKeyState[i] = this->currentKeyState[i];
    glfwPollEvents();
}