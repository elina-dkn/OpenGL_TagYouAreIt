#ifndef SHADER_H
#define SHADER_H

#include "StandardIncludes.h"
class Shader
{
public:
	Shader();
	virtual ~Shader(){}

	GLuint GetProgramID() { return m_programID; }
	GLuint GetAttrColors() { return m_attrColors; }
	GLuint GetAttrVertices() { return m_attrVertices; }
	GLuint GetAttrWVP() { return m_attrWVP; }

	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();


private:
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);

	GLuint m_programID;
	GLuint m_attrVertices;
	GLuint m_attrColors;
	GLint m_result = GL_FALSE;
	GLuint m_attrWVP;
	int m_infoLogLength;
};

#endif