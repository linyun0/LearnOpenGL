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
//protected:
	void moveModel(const glm::vec3& direction);
	void rotateModel(const glm::vec3& direction, const float& degree);
	virtual void getUniforms();
public:
	void UseProgram();
private:
	unsigned int m_shaderProgram;
	unsigned int m_locationProjectionViewMatrix;
	unsigned int m_locationModelMatrix;
	unsigned int m_locationViewMatrix;

	glm::mat4 m_modelMatrix=glm::mat4(1.0f);
	
};
