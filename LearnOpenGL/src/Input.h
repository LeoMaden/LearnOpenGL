#pragma once
#include <GLFW/glfw3.h>

class Input
{
public:
	static void Init(GLFWwindow* window) { s_Window = window; }
	static bool IsKeyDown(int keyCode);
	static bool IsMouseButtonPressed(int mouseButton);

private:
	static GLFWwindow* s_Window;
};