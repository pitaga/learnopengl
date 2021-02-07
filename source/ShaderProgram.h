#pragma once
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <string>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	void start();

	void stop();

	void cleanUp();

	void reloadShader();

protected:
	virtual void getAllUniformLocation() {}
	int getUniformLocation(const std::string& uniformName);
	void loadFloat(int location, float value);
	void loadBoolean(int location, bool value);
	void loadVector(int location, const glm::vec3& vector);
	void loadMatrix(int location, const glm::mat4& matrix);

private:
	int loadShader(const std::string& filePath, int type);
	int createProgram();

private:
	int vertexShaderId;
	int fragmentShaderId;
	int programId;
	std::string vertexFilePath;
	std::string fragmentFilePath;
};

