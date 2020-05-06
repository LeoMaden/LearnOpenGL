#include "Input.h"

GLFWwindow* Input::s_Window;

bool Input::IsKeyDown(int keyCode)
{
	int state = glfwGetKey(s_Window, keyCode);
	return (state == GLFW_PRESS) | (state == GLFW_REPEAT);
}

bool Input::IsMouseButtonPressed(int mouseButton)
{
	int state = glfwGetMouseButton(s_Window, mouseButton);
	return (state == GLFW_PRESS);
}
