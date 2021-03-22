#include <vector>
#include <GL/glew.h>
#include "FileUtil.h"
#include "Exceptions/ShaderExpection.h"
#include "ShaderUtil.h"

using namespace std;

GLuint GetShaderTypeGluint(ShaderType shaderType);

GLuint LoadAndBuildShaderProgram(const string& vsFileName, const string& fragFileName)
{
	const string vertexShaderText = GetFileContents(vsFileName);
	const string fragmentShaderText = GetFileContents(fragFileName);

	return BuildShaderProgram(vertexShaderText, fragmentShaderText);
}

GLuint BuildShaderProgram(const string& vertexShaderText, const string& fragmentShaderText)
{
	GLuint vertexShader = CompileShader(vertexShaderText, ShaderType::Vertex);
	GLuint fragmentShader = CompileShader(fragmentShaderText, ShaderType::Fragment);
	return BuildShaderProgram(vertexShader, fragmentShader);
}

GLuint BuildShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(program);
		throw ShaderExpection(ShaderType::Program, program, &infoLog[0]);
	}
	return program;
}

GLuint CompileShader(const string& shaderText, ShaderType shaderType)
{
	GLuint type = GetShaderTypeGluint(shaderType);
	GLuint shader = glCreateShader(type);

	const char* shaderTextCstr = shaderText.c_str();

	glShaderSource(shader, 1, &shaderTextCstr, NULL);
	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(shader); // Don't leak the shader.

		throw ShaderExpection(shaderType, shader, &errorLog[0]);
	}
	return shader;
}

GLuint GetShaderTypeGluint(ShaderType shaderType)
{
	switch(shaderType)
	{
	case ShaderType::Vertex:
		return GL_VERTEX_SHADER;
	case ShaderType::Fragment:
		return GL_FRAGMENT_SHADER;
	case ShaderType::Program:
		return GL_PROGRAM;
	default:
		return GL_FALSE;
	}
}
