#pragma once

#include <exception>
#include <GL/glew.h>
#include "ShaderType.h"

class ShaderExpection : public std::exception
{
public:
	ShaderExpection(ShaderType shaderType, GLuint shader, const GLchar* infoLog);
	virtual ~ShaderExpection();

	const char* what() const noexcept override;

private:
	const ShaderType m_shaderType;
	const GLuint m_shader;
	const GLchar* m_infoLog;
};
