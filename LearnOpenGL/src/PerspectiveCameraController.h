#pragma once
#include "PerspectiveCamera.h"
#include "Events/Event.h"
#include "Events/MouseMovedEvent.h"

#include <glm/glm.hpp>

class PerspectiveCameraController
{
public:
	PerspectiveCameraController(PerspectiveCamera camera = PerspectiveCamera(60.0f, 1280.0f / 720.0f, 0.1f, 1000.0f));

	void OnUpdate(float ts);
	void OnEvent(Event& e);

	//PerspectiveCamera& GetCamera() { return m_Camera; }
	const PerspectiveCamera& GetCamera() const { return m_Camera; }

private:
	bool OnMouseMoved(MouseMovedEvent& e);

private:
	PerspectiveCamera m_Camera; 
	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraDirection;
	glm::vec3 m_CameraUpDir;
	glm::vec3 m_CameraRightDir;

	float m_Pitch = 0.0f, m_Yaw = 0.0f;
	float m_LastMouseX = 0.0f, m_LastMouseY = 0.0f;

	float m_CameraSpeed = 5.0f;
	float m_LookSensitivity = 0.15f;
};