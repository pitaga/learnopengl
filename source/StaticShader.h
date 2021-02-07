#pragma once
#include "ShaderProgram.h"

const std::string VERTEX_SHADER_FILEPATH = "../shader/vertexShader.vs";
const std::string FRAGMENT_SHADER_FILEPATH = "../shader/fragmentShader.fs";

class StaticShader : public ShaderProgram
{
public:
    StaticShader() : ShaderProgram(VERTEX_SHADER_FILEPATH, FRAGMENT_SHADER_FILEPATH) {
        getAllUniformLocation();
    }

    void loadTransformMatrix(const glm::mat4& matrix) 
    {
        loadMatrix(location_transformMatrix, matrix);
    }

protected:
    virtual void getAllUniformLocation() override 
    {
        location_transformMatrix = getUniformLocation("transformMatrix");
    }

private:
    int location_transformMatrix;
};