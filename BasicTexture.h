#pragma once
#include<iostream>
class BasicTexture
{
public:
	BasicTexture(const std::string& imgName);
	void bindTexture() const;
	void setInt(const std::string& name, int value);

private:
	unsigned int m_textureID;

};
