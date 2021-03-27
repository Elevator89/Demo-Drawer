#include <string>
#include <sstream>
#include "ShaderExpection.h"

using namespace std;

string GetShaderTypeStr(ShaderType shaderType);

ShaderExpection::ShaderExpection(ShaderType shaderType, GLuint shader, const GLchar* infoLog):
	m_shaderType(shaderType),
	m_shader(shader),
	m_infoLog(infoLog)
{}

ShaderExpection::~ShaderExpection() {}

const char* ShaderExpection::what() const noexcept
{
	stringstream ss;
	ss << "Shader exception. Shader: " << m_shader
	   << ", type: " << GetShaderTypeStr(m_shaderType)
	   << ", Message: " << m_infoLog;
	return ss.str().c_str();
}

string GetShaderTypeStr(ShaderType shaderType)
{
	switch(shaderType)
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
