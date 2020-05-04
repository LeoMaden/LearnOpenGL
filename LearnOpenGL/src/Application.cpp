#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"


// Adjust viewport when window is resized.
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static Camera camera({ 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, -1.0f });
static float cameraSpeed = 0.05f;

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		glm::vec3 forward = glm::normalize(glm::vec3(camera.Direction.x, 0.0f, camera.Direction.z));
		camera.CameraPos += cameraSpeed * forward;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		glm::vec3 forward = glm::normalize(glm::vec3(camera.Direction.x, 0.0f, camera.Direction.z));
		camera.CameraPos -= cameraSpeed * forward;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		glm::vec3 right = glm::normalize(glm::cross(camera.Direction, camera.Up));
		camera.CameraPos -= cameraSpeed * right;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm::vec3 right = glm::normalize(glm::cross(camera.Direction, camera.Up));
		camera.CameraPos += cameraSpeed * right;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		glm::vec3 up = glm::normalize(camera.Up);
		camera.CameraPos += cameraSpeed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		glm::vec3 up = glm::normalize(camera.Up);
		camera.CameraPos -= cameraSpeed * up;
	}
}

static float lastX = 400.0f, lastY = 300.0f;
static float pitch = 0.0f, yaw = -90.0f;

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.15f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;
}

static GLuint CreateCubeVBO()
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	return VBO;
}

static GLuint CreateCubeIBO()
{
	GLuint indices[]{
		0, 1, 2, 2, 3, 0,
		1, 2, 6, 6, 5, 1,
		0, 1, 5, 5, 4, 0, 
		3, 0, 4, 4, 7, 3,
		2, 3, 7, 7, 6, 2,
		4, 5, 6, 6, 7, 4
	};

	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	return IBO;
}

static GLuint CreateCubeVAO()
{
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO = CreateCubeVBO();
	//GLuint IBO = CreateCubeIBO();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

	return VAO;
}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	// Check window has been created successfully.
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	
	// Check glad has initialised.
	int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (gladStatus == NULL)
	{
		std::cout << "Failed to initialise glad" << std::endl;
		return EXIT_FAILURE;
	}

	// Glad and GLFW window success.
	std::cout << "[OpenGL] " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "[OpenGL] " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "[OpenGL] " << glGetString(GL_VERSION) << std::endl;

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	glfwSwapInterval(1);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, MouseCallback);

	glEnable(GL_DEPTH_TEST);

	Shader objShader(
		"assets/shaders/basic.glsl.vert",
		"assets/shaders/basic.glsl.frag"
	); 
	Shader lightShader(
		"assets/shaders/light.glsl.vert",
		"assets/shaders/light.glsl.frag"
	);



	GLuint cubeVAO = CreateCubeVAO();

	//glm::vec3 lightPos(1.5f, 2.0f, 2.5f)
	glm::vec3 lightPos;

	glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	glm::vec3& cameraPos = camera.CameraPos;
	cameraPos += glm::vec3(0.0f, 2.0f, 0.0f);

	glm::vec3 lightColor(0.8f, 0.3f, 0.4f);

	// Light uniforms.
	lightShader.Bind();

	lightShader.SetUniform3f("u_LightColor", lightColor.x, lightColor.y, lightColor.z);
	lightShader.SetUniformMat4fv("u_Proj", projection);

	// Object uniforms.
	objShader.Bind();
	glm::mat4 model(1.0f);
	model = glm::scale(model, glm::vec3(2.0f));
	//model = glm::rotate(model, (float)glfwGetTime(), { 1.0f, 1.0f, 0.0f });
	objShader.SetUniformMat4fv("u_Model", model);

	objShader.SetUniform3f("u_LightColor", lightColor.x, lightColor.y, lightColor.z);
	objShader.SetUniformMat4fv("u_Proj", projection);


	// Main loop.
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glm::mat4 view = camera.GetViewMatrix();
		glBindVertexArray(cubeVAO);

		// Draw light.
		lightShader.Bind();
		glm::mat4 lightModel(1.0f);
		lightPos.x = 4 * std::sin(glfwGetTime());
		lightPos.y = 1.5f;
		lightPos.z = 4 * std::cos(glfwGetTime());
		lightModel = glm::translate(lightModel, lightPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.3f));
		lightShader.SetUniformMat4fv("u_Model", lightModel);
		lightShader.SetUniformMat4fv("u_View", view);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Draw object.
		objShader.Bind();
		objShader.SetUniform3f("u_ViewPos", cameraPos.x, cameraPos.y, cameraPos.z);
		objShader.SetUniform3f("u_LightPos", lightPos.x, lightPos.y, lightPos.z);
		objShader.SetUniformMat4fv("u_View", view);

		glDrawArrays(GL_TRIANGLES, 0, 36);


		pitch = pitch > 89.0f ? 89.0f : pitch;
		pitch = pitch < -89.0f ? -89.0f : pitch;

		camera.Direction.x += std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
		camera.Direction.y += std::sin(glm::radians(pitch));
		camera.Direction.z += std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
		camera.Direction = glm::normalize(camera.Direction);

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	glfwTerminate();
	return EXIT_SUCCESS;
}