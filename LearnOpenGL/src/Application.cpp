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

static GLuint CreateCubeVBO()
{
	float vertices[] = {
	//        Position              Normal        Tex
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

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

	GLFWwindow* window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL);

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

	glViewport(0, 0, 1280, 720);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	glfwSwapInterval(1);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);


	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
		MouseMovedEvent e(xPos, yPos);
		Callback(e);
	});

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
		MouseScrolledEvent e(xOffset, yOffset);
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

	Texture box("assets/images/container2.png");
	Texture specMap("assets/images/container2_specular.png");

	box.Bind(0);
	specMap.Bind(1);


	GLuint cubeVAO = CreateCubeVAO();

	//glm::vec3 lightPos(1.5f, 2.0f, 2.5f)
	glm::vec3 lightPos(1.0f, 3.5f, 4.0f);
	cameraController.SetPosition({ 0.0f, 0.0f, 3.0f }); 

	// Light uniforms.
	lightShader.Bind();
	lightShader.SetVec3("u_LightColor", { 1.0f, 1.0f, 1.0f });

	// Object uniforms.
	objShader.Bind();
	glm::mat4 model(1.0f);
	model = glm::scale(model, glm::vec3(2.0f));
	objShader.SetMat4("u_Model", model);

	objShader.SetInt("u_Material.Texture", 0);
	objShader.SetInt("u_Material.Specular", 1);
	objShader.SetFloat("u_Material.Shininess", 0.4*128);

	objShader.SetVec3("u_Light.Position", lightPos);

	objShader.SetVec3("u_Light.Ambient", glm::vec3(0.2f));
	objShader.SetVec3("u_Light.Diffuse", glm::vec3(0.5f));
	objShader.SetVec3("u_Light.Specular", glm::vec3(1.0f));

	float lastFrameTime = 0.0f;
	float currentFrameTime = 0.0f;

	// Main loop.
	while (!glfwWindowShouldClose(window))
	{
		currentFrameTime = glfwGetTime();
		float ts = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		//LOG_INFO("Frame time: {0:.2f}ms ({1:.0f} fps)", 1000*ts, 1.0f / ts);

		cameraController.OnUpdate(ts);

		glm::mat4 viewProjection = cameraController.GetCamera().GetViewProjectionMatrix();
		glBindVertexArray(cubeVAO);

		// Draw light.
		lightShader.Bind();
		glm::mat4 lightModel(1.0f);
		//lightPos.x = 4 * std::sin(glfwGetTime());
		//lightPos.y = 1.5f;
		//lightPos.z = 4 * std::cos(glfwGetTime());
		lightModel = glm::translate(lightModel, lightPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.3f));
		lightShader.SetMat4("u_Model", lightModel);
		lightShader.SetMat4("u_ViewProjection", viewProjection);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Draw object.
		objShader.Bind();
		objShader.SetVec3("u_ViewPos", cameraController.GetCamera().GetPosition());
		objShader.SetVec3("u_LightPos", lightPos);
		objShader.SetMat4("u_ViewProjection", viewProjection);

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