#include "Shader.h"

#include <sstream>
#include <fstream>
#include <iostream>


static std::string ReadFromFile(const std::string& path)
{
	std::stringstream shaderCode;
	std::ifstream file;

	file.open(path.c_str());

	if (!file)
	{
		std::cout << "[Shader] Error opening file " << path << std::endl;
		throw;
	}

	char temp[256];
	while (file.getline(temp, 256))
	{
		shaderCode << temp << "\n";
	}

	file.close();

	std::string code = shaderCode.str();

	return code;
}

static GLuint CreateShader(const char* shaderSrc, GLenum type)
{
	GLuint id = glCreateShader(type);

	glShaderSource(id, 1, &shaderSrc, nullptr);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		char infoLog[512];
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		std::cout << "[OpenGL] Failed to compile shader\n" << infoLog << std::endl;
		throw;
	}

	return id;
}


Shader::Shader(const std::string& vertSrcPath, const std::string& fragSrcPath)
{
	std::string vertSrc = ReadFromFile(vertSrcPath);
	std::string fragSrc = ReadFromFile(fragSrcPath);


	GLuint vertShader, fragShader;

	vertShader = CreateShader(vertSrc.c_str(), GL_VERTEX_SHADER);
	fragShader = CreateShader(fragSrc.c_str(), GL_FRAGMENT_SHADER);

	m_ProgramId = glCreateProgram();
	glAttachShader(m_ProgramId, vertShader);
	glAttachShader(m_ProgramId, fragShader);
	glLinkProgram(m_ProgramId);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramId);
}

void Shader::Bind()
{
	glUseProgram(m_ProgramId);
}

void Shader::SetUniform1f(const std::string& name, float val)
{
	int loc = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform1f(loc, val);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	int loc = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform3f(loc, v0, v1, v2);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	int loc = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform4f(loc, v0, v1, v2, v3);
}

void Shader::SetUniformMat4fv(const std::string& name, glm::mat4 matrix)
{
	int loc = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniform1iv(const std::string& name, int count, int* values)
{
	int loc = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform1iv(loc, count, values);
}


