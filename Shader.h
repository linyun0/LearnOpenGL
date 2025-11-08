#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> 
class Shader {
	
public:
	Shader(std::string& vertexShaderPath, std::string& fragmentShaderPath);
	void loadProjectionViewMatrix(const glm::mat4& pvMatrix);
	void loadModelMatrix(const glm::mat4& matrix);
	void loadViewMatrix(const glm::mat4& matrix);
protected:
	virtual void getUniforms();
public:
	void UseProgram();
private:
	unsigned int m_shaderProgram;
	unsigned int m_locationProjectionViewMatrix;
	unsigned int m_locationModelMatrix;
	unsigned int m_locationViewMatrix;
	
};
