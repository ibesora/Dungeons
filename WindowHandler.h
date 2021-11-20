#pragma once
#include <GLFW/glfw3.h>

class WindowHandler {
public:
	WindowHandler(WindowHandler &other) = delete;
	void operator=(const WindowHandler &) = delete;
	static WindowHandler &getInstance();
	void initWindowAndDevice(int screenWidth, int screenHeight, const char *title, int targetFPS);
	void closeWindow(void);
	bool shouldClose();
	GLFWwindow *getWindow();
	void beginDrawing();
	void endDrawing();
protected:
	WindowHandler();
	GLFWwindow *window;
	double targetTime;
	double currentTime;
	double previousTime;
	double frameTime;
private:
	static void ErrorCallback(int error, const char *description);
	void initWindow(int width, int height, const char *title);
	void initGraphicsDevice(int width, int height);
	void setTargetFPS(int fps);
	void syncFrame(void);
};

