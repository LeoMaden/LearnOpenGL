#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "OpenGL/Shader.h"
#include "OpenGL/Texture.h"
#include "PerspectiveCameraController.h"
#include "Log.h"
#include "Input.h"
#include "OpenGL/Debug.h"


// Adjust viewport when window is resized.
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	/*if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
{
	glfwSetWindowShouldClose(window, true);
}
if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
{
	glm::vec3 forward = glm::normalize(glm::vec3(Camera.GetDirection().x, 0.0f, Camera.GetDirection().z));
	Camera.SetPosition(Camera.GetPosition() + cameraSpeed * forward);
}
if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
{
	glm::vec3 forward = glm::normalize(glm::vec3(Camera.GetDirection().x, 0.0f, Camera.GetDirection().z));
	Camera.SetPosition(Camera.GetPosition() - cameraSpeed * forward);
}
if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
{
	glm::vec3 right = glm::normalize(glm::cross(Camera.GetDirection(), Camera.GetUpDir()));
	Camera.SetPosition(Camera.GetPosition() - cameraSpeed * right);
}
if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
{
	glm::vec3 right = glm::normalize(glm::cross(Camera.GetDirection(), Camera.GetUpDir()));
	Camera.SetPosition(Camera.GetPosition() + cameraSpeed * right);
}
if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
{
	glm::vec3 up = glm::normalize(Camera.GetUpDir());
	Camera.SetPosition(Camera.GetPosition() + cameraSpeed * up);
}
if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
{
	glm::vec3 up = glm::normalize(Camera.GetUpDir());
	Camera.SetPosition(Camera.GetPosition() - cameraSpeed * up);
}*/
}

static float lastX = 400.0f, lastY = 300.0f;
static float pitch = 0.0f, yaw = -90.0f;

//void MouseCallback(GLFWwindow* window, double xpos, double ypos)
//{
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
//	lastX = xpos;
//	lastY = ypos;
//
//	const float sensitivity = 0.15f;
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//
//	yaw += xoffset;
//	pitch += yoffset;
//}

static GLuint CreateCubeVBO()
{
	float vertices[] = {
	//        Position              Normal
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

static PerspectiveCameraController cameraController;

static void Callback(Event& e)
{
	cameraController.OnEvent(e);
}


int main()
{
	Logger::Init();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); 

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	// Check window has been created successfully.
	ASSERT(window, "Error creating GLFW window");
	glfwMakeContextCurrent(window);
	
	// Check glad has initialised.
	int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	ASSERT(gladStatus, "Failed to initialise glad");

	glDebugMessageCallback(OpenGLDebugCallback, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	// Glad and GLFW window success.
	LOG_INFO((const char*)glGetString(GL_VENDOR));
	LOG_INFO(glGetString(GL_RENDERER));
	LOG_INFO(glGetString(GL_VERSION));

	Input::Init(window);

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	glfwSwapInterval(1);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);


	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
		MouseMovedEvent e(xPos, yPos);
		Callback(e);
	});

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

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

	// Light uniforms.
	lightShader.Bind();

	lightShader.SetVec3("u_LightColor", lightColor);
	lightShader.SetMat4("u_Proj", projection);

	// Object uniforms.
	objShader.Bind();
	glm::mat4 model(1.0f);
	model = glm::scale(model, glm::vec3(2.0f));
	//model = glm::rotate(model, (float)glfwGetTime(), { 1.0f, 1.0f, 0.0f });
	objShader.SetMat4("u_Model", model);

	objShader.SetVec3("u_LightColor", lightColor);
	objShader.SetMat4("u_Proj", projection);


	// Main loop.
	while (!glfwWindowShouldClose(window))
	{
		cameraController.OnUpdate(1.0f / 60.0f);

		glm::mat4 view = cameraController.GetCamera().GetViewMatrix();
		glBindVertexArray(cubeVAO);

		// Draw light.
		lightShader.Bind();
		glm::mat4 lightModel(1.0f);
		lightPos.x = 4 * std::sin(glfwGetTime());
		lightPos.y = 1.5f;
		lightPos.z = 4 * std::cos(glfwGetTime());
		lightModel = glm::translate(lightModel, lightPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.3f));
		lightShader.SetMat4("u_Model", lightModel);
		lightShader.SetMat4("u_View", view);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Draw object.
		objShader.Bind();
		objShader.SetVec3("u_ViewPos", cameraController.GetCamera().GetPosition());
		objShader.SetVec3("u_LightPos", lightPos);
		objShader.SetMat4("u_View", view);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, true);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	glfwTerminate();
	std::cin.get();
	return EXIT_SUCCESS;
}