#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "Utils.h"

#define numVAOs 1
#define numVBOs 2

float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// 分配在 display() 函数中使用的变量空间，这样它们就不必在渲染过程中分配
GLuint vLoc, projLoc, tfLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat;

void setupVertices(void);
void init(GLFWwindow* window);
void display(GLFWwindow* window, double currentTime);


int main(void)
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(800, 600, "ch04", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGL()) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	init(window);

	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


// 36 个顶点，12 个三角形，组成了放置在原点处的 2x2x2 立方体
void setupVertices(void)
{
	float vertexPositions[108] = {
		-1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  1.0f, 1.0f,  1.0f, -1.0f,
		1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, -1.0f,
		1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f
	};
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

void init(GLFWwindow* window)
{
	renderingProgram = Utils::createShaderProgram("../../shader/vertShader.vs", "../../shader/fragShader.fs");
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 402.0f;
	cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;		// 沿 Y 周下移以展示透视
	setupVertices();
}

void display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);

	// 获取 MV 矩阵和投影矩阵的统一变量
	vLoc = glGetUniformLocation(renderingProgram, "v_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	tfLoc = glGetUniformLocation(renderingProgram, "tf");

	// 构建透视矩阵
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);	// 1.0472 radians = 60 degrees

	// 构建视图矩阵
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

	for (int i = 0; i < 24; ++i)
	{
		float tf = currentTime + i;

		// 构建和变换模型矩阵的计算已经移动到顶点着色器中去了
		glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
		glUniform1f(tfLoc, tf);

		// 将 VBO 关联给顶点着色器中相应的顶点属性
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		// 调整 OpenGL 设置，绘制模型
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100000);
	}
}
