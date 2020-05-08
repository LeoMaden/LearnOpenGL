#pragma once

#include "glm/glm.hpp"

class PerspectiveCamera
{
public:
	PerspectiveCamera(float fov, float aspect, float near, float far);
	~PerspectiveCamera();

	void SetPerspective(float fov, float aspect, float near, float far);

	void SetPosition(const glm::vec3& position) { m_Position = position; UpdateViewProjectionMatrix(); }
	const glm::vec3& GetPosition() const { return m_Position; }

	void SetDirection(const glm::vec3& direction) { m_Direction = direction; UpdateViewProjectionMatrix(); }
	const glm::vec3& GetDirection() const { return m_Direction; }

	void SetUpDir(const glm::vec3& up) { m_UpDir = up; UpdateViewProjectionMatrix(); }
	glm::vec3& GetUpDir() { return m_UpDir; }

	const glm::vec3& GetRightDirection() const { return m_RightDir; }


	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

	void UpdateViewProjectionMatrix();
	const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	const float GetFov() const { return m_Fov; }
	const float GetAspectRatio() const { return m_AspectRatio; }
	const float GetNearPlaneDist() const { return m_NearPlane; }
	const float GetFarPlaneDist() const { return m_FarPlane; }

	void SetFov(float fov) { m_Fov = fov; SetPerspective(fov, m_AspectRatio, m_NearPlane, m_FarPlane); }
private:
	float m_Fov;
	float m_AspectRatio;
	float m_NearPlane;
	float m_FarPlane;

	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_UpDir;
	glm::vec3 m_RightDir;

	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ViewProjectionMatrix;
};