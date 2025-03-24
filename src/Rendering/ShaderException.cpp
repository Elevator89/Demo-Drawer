#include <string>
#include <sstream>
#include "ShaderException.h"

using namespace std;

string GetShaderTypeStr(ShaderType shaderType);

ShaderException::ShaderException(ShaderType shaderType, GLuint shader, const GLchar* infoLog) :
	m_shaderType(shaderType),
	m_shader(shader),
	m_infoLog(infoLog)
{
	stringstream ss;
	ss << "Shader exception. Shader: " << m_shader
		<< ", type: " << GetShaderTypeStr(m_shaderType)
		<< ", Message: " << m_infoLog;

	m_what = ss.str();
}

ShaderException::~ShaderException() {}

const char* ShaderException::what() const noexcept
{
	return m_what.c_str();
}

string GetShaderTypeStr(ShaderType shaderType)
{
	switch (shaderType)
	{
	case ShaderType::Vertex:
		return "vertex";
	case ShaderType::Fragment:
		return "fragment";
	case ShaderType::Program:
		return "program";
	default:
		return "unknown";
	}
}
