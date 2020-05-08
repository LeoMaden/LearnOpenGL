#pragma once
#include "PerspectiveCamera.h"
#include "Events/Event.h"
#include "Events/MouseMovedEvent.h"
#include "Events/MouseScrolledEvent.h"

#include <glm/glm.hpp>

class PerspectiveCameraController
{
public:
	PerspectiveCameraController(PerspectiveCamera camera = PerspectiveCamera(glm::radians(60.0f), 1280.0f / 720.0f, 0.1f, 1000.0f));

	void OnUpdate(float ts);
	void OnEvent(Event& e);

	const PerspectiveCamera& GetCamera() const { return m_Camera; }

	void SetPosition(const glm::vec3& position) { m_CameraPosition = position; m_Camera.SetPosition(position); }

private:
	bool OnMouseMoved(MouseMovedEvent& e);
	bool OnMouseScrolled(MouseScrolledEvent& e);

private:
	PerspectiveCamera m_Camera; 
	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraDirection;
	glm::vec3 m_CameraUpDir;
	glm::vec3 m_CameraRightDir;

	float m_Pitch = 0.0f, m_Yaw = -90.0f;
	float m_LastMouseX = 0.0f, m_LastMouseY = 0.0f;
	bool m_FirstMove = true;

	float m_CameraSpeed = 5.0f;
	float m_LookSensitivity = 0.15f;
	float m_ZoomSensitivity = 5.0f;
};