#pragma once

#include <string>
#include <glad/glad.h>

class Texture
{
private:
	int m_Width, m_Height, m_Channels;
	unsigned char* m_Data;
	GLuint m_TexId;
public:
	Texture(const std::string& path);

	void Bind(GLuint texSlot = 0);
};