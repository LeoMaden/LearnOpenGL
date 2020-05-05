#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Logger::s_Logger;
std::shared_ptr<spdlog::logger> Logger::s_OpenGLLogger;

void Logger::Init()
{
	s_Logger = spdlog::stdout_color_mt("Logger");

	s_Logger->set_level(spdlog::level::trace);
	s_Logger->set_pattern("%^%T [%n]: %v");


	s_OpenGLLogger = spdlog::stdout_color_mt("OpenGL");

	s_OpenGLLogger->set_level(spdlog::level::trace);
	s_OpenGLLogger->set_pattern("%^%T [%n]: %v");
}

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
