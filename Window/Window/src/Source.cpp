/* GLEW*/
#include <GL/glew.h>

/* GLFW */
#include <GLFW/glfw3.h>

/* GLM*/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Standard */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/* Additional files */
#include "Shaders.cpp"

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL ERROR] (" << error << "): " << function << ": " << file << " (" << line << ")" << std::endl;
		return false;
	}
	return true;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Exercise #3", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Couldn't load GLEW." << std::endl;
	}
		
	/* Prints current openGL version */
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[] =
	{
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f,
	};
	
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	/* buffer ID*/
	unsigned int buffer; 

	/* Generate a buffer*/
	GLCall(glGenBuffers(1, &buffer));

	/* select buffer*/
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));

	/* Specifies buffer data and size*/
	GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_DYNAMIC_DRAW));

	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
	GLCall(glEnableVertexAttribArray(0));
	
	unsigned int ibo;

	/* Generate a buffer*/
	GLCall(glGenBuffers(1, &ibo));

	/* select buffer*/
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

	/* Specifies buffer data and size*/
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW));

	Shaders::ShaderProgramSource source = Shaders::ParseShader("res/shaders/Basic_s.shader");
	unsigned int shader = Shaders::CreateShader(source.VertexSource, source.FragmentSource);
	GLCall(glUseProgram(shader));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float value = sin(glfwGetTime()) / 2.0f + 0.5f;
		
		/* Render here */
		//glClearColor(0.231, 0.494, 0.890, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr));

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */	
		glfwPollEvents();
	}

	GLCall(glDeleteProgram(shader));
	GLCall(glfwTerminate());
	return 0;
}