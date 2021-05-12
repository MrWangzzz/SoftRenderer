#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<glm/glm.hpp>
#include "Math.h"
#include<string>
#include <vector>
using namespace std;

int Width = 800;
int Height = 600;
float vertices[] =
{
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f,
};

unsigned int VBO;
unsigned int VAO;



const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;
int main()
{
	glfwInit();//初始化Glfw
	//创建窗口
	GLFWwindow* window = glfwCreateWindow(Width, Height, "MeiLinFirstOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to creat GLFW Window" << std::endl;
		//销毁所有窗口
		glfwTerminate();
		return -1;
	}
	//将window窗口作为当前线程的上下文
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, Width, Height);



	while (!glfwWindowShouldClose(window))//简单的循环渲染
	{
		////这里处理渲染命令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glGenBuffers(1, &VBO);//顶点缓冲 

		glBindBuffer(GL_ARRAY_BUFFER, VBO);


		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glUseProgram(shaderProgram);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		// 2. 把顶点数组复制到缓冲中供OpenGL使用
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 3. 设置顶点属性指针
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);




		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();//检测有没有触发什事件

		glfwSwapBuffers(window);//交换缓冲，输出在屏幕
	}
	glfwTerminate();//释放资源
	return 0;
}
