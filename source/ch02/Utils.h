#pragma once
#include <glad/glad.h>
#include <string>


class Utils
{
public:
	static GLuint createShaderProgram(const std::string& vertShaderPath, const std::string& fragShaderPath);
	static void printShaderLog(GLuint shader);
	static void printProgramLog(int prog);
	static bool checkOpenGLError();
	static std::string readShaderSource(const char* filePath);
};

