#include "PerspectiveCameraController.h"
#include "Input.h"
#include "GLFW/glfw3.h"


PerspectiveCameraController::PerspectiveCameraController(PerspectiveCamera camera)
	: m_Camera(camera), m_CameraPosition(camera.GetPosition())
	, m_CameraDirection(camera.GetDirection()), m_CameraUpDir(camera.GetUpDir())
	, m_CameraRightDir(camera.GetRightDirection())
{
}

void PerspectiveCameraController::OnUpdate(float ts)
{
	if (Input::IsKeyDown(GLFW_KEY_W))
	{
		m_CameraPosition.x += m_CameraDirection.x * m_CameraSpeed * ts;
		m_CameraPosition.y += m_CameraDirection.y * m_CameraSpeed * ts;
		m_CameraPosition.z += m_CameraDirection.z * m_CameraSpeed * ts;
	}
	if (Input::IsKeyDown(GLFW_KEY_S))
	{
		m_CameraPosition.x -= m_CameraDirection.x * m_CameraSpeed * ts;
		m_CameraPosition.y -= m_CameraDirection.y * m_CameraSpeed * ts;
		m_CameraPosition.z -= m_CameraDirection.z * m_CameraSpeed * ts;
	}
	if (Input::IsKeyDown(GLFW_KEY_A))
	{
		m_CameraPosition.x -= m_CameraRightDir.x * m_CameraSpeed * ts;
		m_CameraPosition.y -= m_CameraRightDir.y * m_CameraSpeed * ts;
		m_CameraPosition.z -= m_CameraRightDir.z * m_CameraSpeed * ts;
	}
	if (Input::IsKeyDown(GLFW_KEY_D))
	{
		m_CameraPosition.x += m_CameraRightDir.x * m_CameraSpeed * ts;
		m_CameraPosition.y += m_CameraRightDir.y * m_CameraSpeed * ts;
		m_CameraPosition.z += m_CameraRightDir.z * m_CameraSpeed * ts;
	}
	if (Input::IsKeyDown(GLFW_KEY_SPACE))
	{
		m_CameraPosition.x += m_CameraUpDir.x * m_CameraSpeed * ts;
		m_CameraPosition.y += m_CameraUpDir.y * m_CameraSpeed * ts;
		m_CameraPosition.z += m_CameraUpDir.z * m_CameraSpeed * ts;
	}
	if (Input::IsKeyDown(GLFW_KEY_LEFT_SHIFT))
	{
		m_CameraPosition.x -= m_CameraUpDir.x * m_CameraSpeed * ts;
		m_CameraPosition.y -= m_CameraUpDir.y * m_CameraSpeed * ts;
		m_CameraPosition.z -= m_CameraUpDir.z * m_CameraSpeed * ts;
	}

	m_Camera.SetPosition(m_CameraPosition);
}
