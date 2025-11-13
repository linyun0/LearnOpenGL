#include<BasicTexture.h>
#include <qopenglfunctions.h>
#include <qimage.h>
#define STB_IMAGE_IMPLEMENTATION
#include "Resource/Library/stb_image/stb_image.h"
BasicTexture::BasicTexture(const std::string& imgName)
{
	auto glFuncs = QOpenGLContext::currentContext()->functions();

	glFuncs->glGenTextures(1, &m_textureID);
	glFuncs->glBindTexture(GL_TEXTURE_2D, m_textureID);
	glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINE);

	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load(imgName.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glFuncs->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glFuncs->glGenerateMipmap(GL_TEXTURE_2D);
	}
	glFuncs->glActiveTexture(GL_TEXTURE0);
	stbi_image_free(data);

	
}

void BasicTexture::bindTexture() const
{
	auto glFuncs = QOpenGLContext::currentContext()->functions();
	glFuncs->glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void BasicTexture::setInt(const std::string& name, int value)
{
	auto glFuncs = QOpenGLContext::currentContext()->functions();
	glFuncs->glUniform1i(glFuncs->glGetUniformLocation(m_textureID, name.c_str()), value);
}
