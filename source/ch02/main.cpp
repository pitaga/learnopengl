#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define numVAOS 1
GLuint vao[numVAOS];
GLuint renderingProgram;
float x = 0.0f;
float inc = 0.01f;

void init(GLFWwindow* window);
void display(GLFWwindow* window, double currentTime);
GLuint createShaderProgram();

void printShaderLog(GLuint shader);
void printProgramLog(int prog);
bool checkOpenGLError();

std::string readShaderSource(const char* filePath);


int main(void)
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 400, "ch02", NULL, NULL);
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


void init(GLFWwindow* window)
{
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOS, vao);
	glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(renderingProgram);
	glClear(GL_COLOR_BUFFER_BIT);
	//glPointSize(30);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	x += inc;						// 切换至让三角形向右移动
	if (x > 1.0f) inc = -0.01f;		// 沿 x 轴移动三角形
	if (x < -1.0f) inc = 0.01f;		// 切换至三角形向左移动
	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");	// 获取 "offset" 指针
	glProgramUniform1f(renderingProgram, offsetLoc, x);		// 将 "x" 中的值传给 "offset"

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint createShaderProgram()
{
	std::string vertSourceStr = readShaderSource("../../shader/vertShader.vs");
	std::string fragSourceStr = readShaderSource("../../shader/fragShader.fs");

	const char* vshaderSource = vertSourceStr.c_str();
	const char* fshaderSource = fragSourceStr.c_str();

	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vshaderSource, NULL);
	glCompileShader(vshader);
	GLint vertCompiled;
	checkOpenGLError();
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1) {
		std::cout << "vertex compilation failed" << std::endl;
		printShaderLog(vshader);
	}

	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fshaderSource, NULL);
	glCompileShader(fshader);
	GLint fragCompiled;
	checkOpenGLError();
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1) {
		std::cout << "fragment compilation failed" << std::endl;
		printShaderLog(fshader);
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vshader);
	glAttachShader(program, fshader);
	glLinkProgram(program);
	GLint linked;
	checkOpenGLError();
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		std::cout << "linking failed" << std::endl;
		printShaderLog(program);
	}

	return program;
}

void printShaderLog(GLuint shader)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		std::cout << "Shader Info Log: " << log << std::endl;
		free(log);
	}
}

void printProgramLog(int prog)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "Program Info Log: " << log << std::endl;
		free(log);
	}
}

bool checkOpenGLError()
{
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		std::cout << "glError: " << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

std::string readShaderSource(const char* filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}
