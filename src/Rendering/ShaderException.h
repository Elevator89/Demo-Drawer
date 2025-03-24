#pragma once

#include <exception>
#include <glad/gl.h>
#include "ShaderType.h"

class ShaderException : public std::exception
{
public:
	ShaderException(ShaderType shaderType, GLuint shader, const GLchar* infoLog);
	virtual ~ShaderException();

	const char* what() const noexcept override;

private:
	const ShaderType m_shaderType;
	const GLuint m_shader;
	const GLchar* m_infoLog;
	std::string m_what;
};
