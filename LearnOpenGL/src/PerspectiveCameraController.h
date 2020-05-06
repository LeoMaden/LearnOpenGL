#pragma once
#include "PerspectiveCamera.h"

#include <glm/glm.hpp>

class PerspectiveCameraController
{
public:
	PerspectiveCameraController(PerspectiveCamera camera = PerspectiveCamera(60.0f, 1280.0f / 720.0f, 0.1f, 1000.0f));
	void OnUpdate(float ts);

public:
	PerspectiveCamera m_Camera; 
	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraDirection;
	glm::vec3 m_CameraUpDir;
	glm::vec3 m_CameraRightDir;

	float m_CameraSpeed = 5.0f;
};