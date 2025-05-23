#pragma once

#include <glad/gl.h>
#include <string>
#include "ShaderType.h"

GLuint LoadAndBuildShaderProgram(const std::string& vsFileName, const std::string& fragFileName);
GLuint BuildShaderProgram(const std::string& vertexShaderText, const std::string& fragmentShaderText);
GLuint BuildShaderProgram(GLuint vertexShader, GLuint fragmentShader);
GLuint CompileShader(const std::string& shaderText, ShaderType shaderType);
