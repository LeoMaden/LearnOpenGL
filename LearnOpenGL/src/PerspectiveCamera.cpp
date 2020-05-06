#include "PerspectiveCamera.h"

#include "glm/gtc/matrix_transform.hpp"

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
	: m_Position(0.0f), m_Direction(0.0f, 0.0f, -1.0f), m_UpDir(0.0f, 1.0f, 0.0f)
{
	m_RightDir = glm::normalize(glm::cross(m_Direction, m_UpDir));
	m_ProjectionMatrix = glm::perspective(fov, aspect, near, far);

	UpdateViewProjectionMatrix();
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::SetPerspective(float fov, float aspect, float near, float far)
{
	m_ProjectionMatrix = glm::perspective(fov, aspect, near, far);

	UpdateViewProjectionMatrix();
}

void PerspectiveCamera::UpdateViewProjectionMatrix()
{
	m_RightDir = glm::normalize(glm::cross(m_Direction, m_UpDir));
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Direction, m_UpDir);

	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
