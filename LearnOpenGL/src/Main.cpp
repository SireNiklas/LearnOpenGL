#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"

// Function Declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void proccessInput(GLFWwindow* window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {

#pragma region Create Window
	// Initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window Creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLAD: Load all function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
#pragma endregion

	Shader ourShader("C:/dev/cpp/LearnOpenGL/LearnOpenGL/src/shaders/shader.vert", "C:/dev/cpp/LearnOpenGL/LearnOpenGL/src/shaders/shader.frag");

	// Triangle
	float vertices[] = {
		// Positions			// Colors
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	// Bottom Right | Red
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	// Bottom Left | Green
		 0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f	// Top | Blue
	};

	// Square
	//float vertices[] = {
	//	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	// Top | Blue
	//	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	// Bottom Right | Red
	//	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	// Bottom Left | Green
	//	-0.5f,  0.5f, 0.0f,		1.0f, 0.9f, 0.0f	// Top | Blue 
	//};

	unsigned int indices[] = {
		0, 1, 3,	// First Triangle
		1, 2, 3		// Second Triangle
	};

#pragma region OpenGL Graphics Pipeline
	// Create VBO & VAO
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind Vertext Array Object first, the bind and set buffers
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
#pragma endregion

	float hOffsetValue = 0;
	float vOffsetValue = 0;
	bool moveRight = true;

	// Render Loop
	while (!glfwWindowShouldClose(window)) {
		// Proccess Input
		proccessInput(window);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Drawn Triangle
		ourShader.use();
		//glUseProgram(shaderProgram);

		//float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		ourShader.setFloat("hOffset", hOffsetValue);
		//ourShader.setFloat("vOffset", vOffsetValue);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		if (moveRight) {

			if (hOffsetValue <= 0.5f) {
				hOffsetValue += 0.005f;
			}
			else {
				moveRight = false;
			}
			if (vOffsetValue <= 0.5f) {
				vOffsetValue += 0.005f;
			}

		}
		else {
			if (hOffsetValue >= -0.5f) {
				hOffsetValue -= 0.005f;
			}
			else
			{
				moveRight = true;
			}
			if (vOffsetValue >= -0.5f) {
				vOffsetValue -= 0.005f;
			}
			else
			{
				moveRight = true;
			}
		}
		std::cout << hOffsetValue << std::endl;
		std::cout << vOffsetValue << std::endl;

		// Swap Buffers and Pull IO Events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// GL Cleanup | Optional
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//glDeleteProgram(shaderProgram);

	// GLFW Cleanup
	glfwTerminate();
	return 0;
}

// Window Resize by OS or User, execute this callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

}

// Proccess input
void proccessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}