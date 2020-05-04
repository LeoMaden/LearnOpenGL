#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	glm::vec3 CameraPos;
	glm::vec3 Direction;
	glm::vec3 Up;
public:
	Camera(const glm::vec3& position, const glm::vec3& direction);

	glm::mat4 GetViewMatrix() const;

};