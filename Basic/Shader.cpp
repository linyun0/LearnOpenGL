#include "Shader.h"
#include <qopenglfunctions.h>
#include <iostream>
#include "Utils/FileUtil.h"
//
//
//Shader::Shader(std::string& vertexShaderPath, std::string& fragmentShaderPath)
//{
//    unsigned int vertexshader, fragmentshader;
//
//    QOpenGLFunctions* glFuncs = QOpenGLContext::currentContext()->functions();
//    
//    std::string tempStr =  getFileContents(vertexShaderPath);
//    const char* vertexShaderSource = tempStr.c_str();
//
//    unsigned int vertexShader = glFuncs->glCreateShader(GL_VERTEX_SHADER);
//    glFuncs->glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glFuncs->glCompileShader(vertexShader);
//    // check for shader compile errors
//    int success;
//    char infoLog[512];
//    glFuncs->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glFuncs->glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//    // fragment shader
//    unsigned int fragmentShader = glFuncs->glCreateShader(GL_FRAGMENT_SHADER);
//    tempStr =  getFileContents(fragmentShaderPath);
//    const char* fragmentShaderSource = tempStr.c_str();
//    glFuncs->glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glFuncs->glCompileShader(fragmentShader);
//    // check for shader compile errors
//    glFuncs->glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glFuncs->glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//    // link shaders
//    m_shaderProgram = glFuncs->glCreateProgram();
//    glFuncs->glAttachShader(m_shaderProgram, vertexShader);
//    glFuncs->glAttachShader(m_shaderProgram, fragmentShader);
//    glFuncs->glLinkProgram(m_shaderProgram);
//    // check for linking errors
//    glFuncs->glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
//    if (!success) {
//        glFuncs->glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//    }
//    glFuncs->glDeleteShader(vertexShader);
//    glFuncs->glDeleteShader(fragmentShader);
//
//    
//    getUniforms();
//}
//
//void Shader::moveModel(const glm::vec3& direction)
//{
//    m_modelMatrix = glm::translate(m_modelMatrix, direction);
//    this->UseProgram();
//    this->loadModelMatrix(m_modelMatrix);
//}
//
//void Shader::rotateModel(const glm::vec3& direction, const float& degree)
//{
//    m_modelMatrix = glm::rotate(m_modelMatrix, degree, direction);
//    this->UseProgram();
//    this->loadModelMatrix(m_modelMatrix);
//}
//
//void Shader::getUniforms()
//{
//    auto glFuncs = QOpenGLContext::currentContext()->functions();
//    m_locationModelMatrix = glFuncs->glGetUniformLocation(m_shaderProgram, "model");
//    m_locationViewMatrix = glFuncs->glGetUniformLocation(m_shaderProgram, "view");
//    m_locationProjectionViewMatrix = glFuncs->glGetUniformLocation(m_shaderProgram, "projection");
//    
//}
//
//void Shader::loadProjectionViewMatrix(const glm::mat4& pvMatrix)
//{
//    auto glFuncs = QOpenGLContext::currentContext()->functions();
//    glFuncs->glUniformMatrix4fv(m_locationProjectionViewMatrix,
//        1, GL_FALSE, glm::value_ptr(pvMatrix));
//}
//
//void Shader::loadModelMatrix(const glm::mat4& matrix)
//{
//    
//    auto glFuncs = QOpenGLContext::currentContext()->functions();
//    glFuncs->glUniformMatrix4fv(m_locationModelMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
//}
//
//void Shader::loadViewMatrix(const glm::mat4& matrix)
//{
//    auto glFuncs = QOpenGLContext::currentContext()->functions();
//    glFuncs->glUniformMatrix4fv(m_locationViewMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
//}
//
//void Shader::UseProgram()
//{
//    auto glFuncs = QOpenGLContext::currentContext()->functions();
//    
// //   glFuncs->initializeOpenGLFunctions();
//    glFuncs->glUseProgram(m_shaderProgram);
//}
