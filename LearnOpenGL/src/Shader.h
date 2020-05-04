#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
private:
	GLuint m_ProgramId;
public:
	Shader(const std::string& vertSrcPath, const std::string& fragSrcPath);
	~Shader();

	void Bind();

	void SetUniform1f(const std::string& name, float val);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	void SetUniformMat4fv(const std::string& name, glm::mat4 matrix);

	void SetUniform1iv(const std::string& name, int count, int* values);
};

