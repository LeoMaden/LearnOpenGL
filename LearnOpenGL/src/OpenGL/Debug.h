#pragma once

#include <glad/glad.h>
#include "Log.h"


void OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		Logger::s_OpenGLLogger->error(message);
	case GL_DEBUG_SEVERITY_MEDIUM:
		Logger::s_OpenGLLogger->warn(message);
	case GL_DEBUG_SEVERITY_LOW:
		Logger::s_OpenGLLogger->info(message);
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		Logger::s_OpenGLLogger->debug(message);
	}
}