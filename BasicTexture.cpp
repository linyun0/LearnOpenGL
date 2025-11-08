#include<BasicTexture.h>
#include <qopenglfunctions.h>
#include <qimage.h>
#define STB_IMAGE_IMPLEMENTATION
#include "Resource/Library/stb_image/stb_image.h"
BasicTexture::BasicTexture(const std::string& imgName)
{
	auto glFuncs = QOpenGLContext::currentContext()->functions();
	
	glFuncs->glGenTextures(1, &m_textureID);
	glFuncs->glActiveTexture(GL_TEXTURE0);
	glFuncs->glBindTexture(GL_TEXTURE_2D, m_textureID);
	glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
	glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);

	glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glFuncs->`glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);

	//QImage image(QString::fromLocal8Bit(imgName.c_str()));
	//// 第一步：转换为OpenGL兼容的格式
	//QImage glImage = image.convertToFormat(QImage::Format_RGBA8888);
	//// 第二步：垂直翻转图像（因为Qt和Open和OpenGL的坐标系不同）
	//glImage = glImage.mirrored(false, true);
	//// 第三步：获取数据指针
	//uchar* imagedata = glImage.bits();
	//
	//if (imagedata) {
	//	glFuncs->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
	//		glImage.width(), glImage.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagedata);
	//	glFuncs->glGenerateMipmap(GL_TEXTURE_2D);
	//}

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load(imgName.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glFuncs->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glFuncs->glGenerateMipmap(GL_TEXTURE_2D);
	}
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
