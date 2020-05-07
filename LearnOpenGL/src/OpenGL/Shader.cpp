#include "Shader.h"
#include "Log.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>


static std::string ReadFromFile(const std::string& path)
{
	std::stringstream shaderCode;
	std::ifstream file;

	file.open(path.c_str());

	ASSERT(file, "Failed to open file: {0}", path);

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

void Shader::SetInt(const std::string& name, int value)
{
	int loc = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform1i(loc, value);
}

void Shader::SetFloat(const std::string& name, float value)
{
	int loc = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform1f(loc, value);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& vec)
{
	int loc = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform3f(loc, vec.x, vec.y, vec.z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& vec)
{
	int loc = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& matrix)
{
	int loc = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetIntArray(const std::string& name, const std::vector<int>& values)
{
	int loc = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform1iv(loc, values.size(), values.data());
}


