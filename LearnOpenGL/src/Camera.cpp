#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(const glm::vec3& position, const glm::vec3& direction)
	: CameraPos(position), Direction(direction), Up(0.0f, 1.0f, 0.0f)
{
}


glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(CameraPos, CameraPos + Direction, Up);
}
