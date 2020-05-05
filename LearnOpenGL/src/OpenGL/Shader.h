#pragma once

#include <string>
#include <vector>
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

	void SetFloat(const std::string& name, float value);
	void SetVec3(const std::string& name, const glm::vec3& vec);
	void SetVec4(const std::string& name, const glm::vec4& vec);
	void SetMat4(const std::string& name, const glm::mat4& mat);
	void SetIntArray(const std::string& name, const std::vector<int>& values);
};

