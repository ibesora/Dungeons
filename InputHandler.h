#pragma once
#include <GLFW/glfw3.h>

class InputHandler {
public:
	InputHandler(InputHandler &other) = delete;
	void operator=(const InputHandler &) = delete;
	static InputHandler &getInstance();
	void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	bool isKeyDown(int key);
	bool isKeyPressed(int key);
	void PollInputEvents(void);
protected:
	InputHandler();
	char previousKeyState[512];
	char currentKeyState[512];
};

