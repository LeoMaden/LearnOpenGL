#pragma once

#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include "spdlog/fmt/ostr.h"

class Logger
{
public:
	static void Init();

	static std::shared_ptr<spdlog::logger> s_Logger;
	static std::shared_ptr<spdlog::logger> s_OpenGLLogger;
};

void OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

#define LOG_DEBUG(...) ::Logger::s_Logger->debug(__VA_ARGS__)
#define LOG_INFO(...) ::Logger::s_Logger->info(__VA_ARGS__)
#define LOG_WARN(...) ::Logger::s_Logger->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Logger::s_Logger->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Logger::s_Logger->critical(__VA_ARGS__)

#define ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }