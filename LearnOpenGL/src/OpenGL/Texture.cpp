#include "Texture.h"
#include "Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>


Texture::Texture(const std::string& path)
{
	stbi_set_flip_vertically_on_load(1);
	m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);

	ASSERT(m_Data, "Failed to load texture: {0}", path);

	GLenum channels = m_Channels == 3 ? GL_RGB : GL_RGBA;

	glGenTextures(1, &m_TexId);
	glBindTexture(GL_TEXTURE_2D, m_TexId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, channels, GL_UNSIGNED_BYTE, m_Data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(m_Data);
}

void Texture::Bind(GLuint texSlot)
{
	glActiveTexture(GL_TEXTURE0 + texSlot);
	glBindTexture(GL_TEXTURE_2D, m_TexId);
}
