#include "PerspectiveCameraController.h"
#include "Input.h"
#include "GLFW/glfw3.h"

#include "Log.h"

#include <functional>

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
		//m_CameraPosition.y += m_CameraDirection.y * m_CameraSpeed * ts;
		m_CameraPosition.z += m_CameraDirection.z * m_CameraSpeed * ts;
	}
	if (Input::IsKeyDown(GLFW_KEY_S))
	{
		m_CameraPosition.x -= m_CameraDirection.x * m_CameraSpeed * ts;
		//m_CameraPosition.y -= m_CameraDirection.y * m_CameraSpeed * ts;
		m_CameraPosition.z -= m_CameraDirection.z * m_CameraSpeed * ts;
	}
	if (Input::IsKeyDown(GLFW_KEY_A))
	{
		m_CameraPosition.x -= m_CameraRightDir.x * m_CameraSpeed * ts;
		//m_CameraPosition.y -= m_CameraRightDir.y * m_CameraSpeed * ts;
		m_CameraPosition.z -= m_CameraRightDir.z * m_CameraSpeed * ts;
	}
	if (Input::IsKeyDown(GLFW_KEY_D))
	{
		m_CameraPosition.x += m_CameraRightDir.x * m_CameraSpeed * ts;
		//m_CameraPosition.y += m_CameraRightDir.y * m_CameraSpeed * ts;
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

void PerspectiveCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.Dispatch<MouseMovedEvent>([this](auto& handler) { return this->OnMouseMoved(handler); });
	dispatcher.Dispatch<MouseScrolledEvent>([this](auto& handler) { return this->OnMouseScrolled(handler); });
}

bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& e)
{
	if (m_FirstMove)
	{
		m_LastMouseX = e.GetXPos();
		m_LastMouseY = e.GetYPos();
		m_FirstMove = false;
		return true;
	}

	float deltaX = e.GetXPos() - m_LastMouseX;
	float deltaY = -(e.GetYPos() - m_LastMouseY);

	m_LastMouseX = e.GetXPos();
	m_LastMouseY = e.GetYPos();

	m_Yaw += deltaX * m_LookSensitivity;
	m_Pitch += deltaY * m_LookSensitivity;

	m_Pitch = m_Pitch > 89.0f ? 89.0f : m_Pitch;
	m_Pitch = m_Pitch < -89.0f ? -89.0f : m_Pitch;

	m_CameraDirection.x = std::cos(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch));
	m_CameraDirection.y = std::sin(glm::radians(m_Pitch));
	m_CameraDirection.z = std::sin(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch));

	m_Camera.SetDirection(m_CameraDirection);
	m_CameraRightDir = m_Camera.GetRightDirection();

	return true;
}

bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	float newFov = glm::degrees(m_Camera.GetFov()) - (e.GetYOffset() * m_ZoomSensitivity);

	newFov = newFov > 60.0f ? 60.0f : newFov;
	newFov = newFov < 15.0f ? 15.0f : newFov;

	m_Camera.SetFov(glm::radians(newFov));

	return true;
}
