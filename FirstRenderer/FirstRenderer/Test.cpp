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
	glfwInit();//��ʼ��Glfw
	//��������
	GLFWwindow* window = glfwCreateWindow(Width, Height, "MeiLinFirstOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to creat GLFW Window" << std::endl;
		//�������д���
		glfwTerminate();
		return -1;
	}
	//��window������Ϊ��ǰ�̵߳�������
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, Width, Height);



	while (!glfwWindowShouldClose(window))//�򵥵�ѭ����Ⱦ
	{
		////���ﴦ����Ⱦ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glGenBuffers(1, &VBO);//���㻺�� 

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
		// 2. �Ѷ������鸴�Ƶ������й�OpenGLʹ��
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 3. ���ö�������ָ��
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);




		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();//�����û�д���ʲ�¼�

		glfwSwapBuffers(window);//�������壬�������Ļ
	}
	glfwTerminate();//�ͷ���Դ
	return 0;
}
