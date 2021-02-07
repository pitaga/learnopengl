#include "ShaderProgram.h"
#include "glad/glad.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    vertexFilePath = vertexShaderPath;
    fragmentFilePath = fragmentShaderPath;
    programId = createProgram();
    getAllUniformLocation();
}

void ShaderProgram::start()
{
    glUseProgram(programId);
}

void ShaderProgram::stop()
{
    glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);

    glDeleteProgram(programId);
}

void ShaderProgram::reloadShader()
{
    int reload_program_id = createProgram();
    if (reload_program_id) {
        glDeleteProgram(programId);
        programId = reload_program_id;
    }
}

int ShaderProgram::getUniformLocation(const std::string& uniformName)
{
    return glGetUniformLocation(programId, uniformName.data());
}

void ShaderProgram::loadFloat(int location, float value) 
{
    glUniform1f(location, value);
}

void ShaderProgram::loadBoolean(int location, bool value) 
{
    glUniform1f(location, value ? 1 : 0);
}

void ShaderProgram::loadVector(int location, const glm::vec3& vector) 
{
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::loadMatrix(int location, const glm::mat4& matrix) 
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

int ShaderProgram::loadShader(const std::string& filePath, int type)
{
    std::string strShaderCode;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        std::stringstream shaderStream;
        shaderFile.open(filePath);
        shaderStream << shaderFile.rdbuf();

        shaderFile.close();
        strShaderCode = shaderStream.str();
    }
    catch (std::exception e) {
        std::cout << "laod shader error." << std::endl;
        return -1;
    }

    int shaderId = glCreateShader(type);
    const char* cShaderCode = strShaderCode.c_str();
    glShaderSource(shaderId, 1, &cShaderCode, NULL);
    glCompileShader(shaderId);

    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "compile shader Error. info:" << infoLog << std::endl;
    }

    return shaderId;
}

int ShaderProgram::createProgram()
{
    vertexShaderId = loadShader(vertexFilePath, GL_VERTEX_SHADER);
    fragmentShaderId = loadShader(fragmentFilePath, GL_FRAGMENT_SHADER);
    int pID = glCreateProgram();
    glAttachShader(pID, vertexShaderId);
    glAttachShader(pID, fragmentShaderId);
    glLinkProgram(pID);

    int success;
    glGetProgramiv(pID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(pID, 512, NULL, infoLog);
        std::cout << "link program Error. Info:" << infoLog << std::endl;
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    return pID;
}
