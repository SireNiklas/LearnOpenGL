#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <iostream>

#include "Shader.h"

// Function Declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void proccessInput(GLFWwindow* window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float opacitySwitch = 0;

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

# pragma region Vertex Data
	// Triangle
	//float vertices[] = {
	//	// Positions			// Colors
	//	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	// Bottom Right | Red
	//	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	// Bottom Left | Green
	//	 0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f	// Top | Blue
	//};

	// Square
	float vertices[] = {
		// Positions			// Colors			// Texture Coords
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 1.0f,	1.0f, 1.0f,	// Top Right | Red
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,	// Bottom Right | Green
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,	// Bottom Left | Blue
		-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f	// Top Left | Yellow 
	};

	unsigned int indices[] = {
		0, 1, 3,	// First Triangle
		1, 2, 3		// Second Triangle
	};

	float texCoords[] = {
		0.0f, 0.0f,		// Lower Left Corner
		1.0f, 0.0f,		// Lower Right Corner
		0.5f, 1.0f		// Top Center Corner
	};
#pragma endregion

#pragma region Textures
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);

	// Bind Texture
	glBindTexture(GL_TEXTURE_2D, texture1);

	// Configurations
	// Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("C:/dev/cpp/LearnOpenGL/LearnOpenGL/src/resources/container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);

	data = stbi_load("C:/dev/cpp/LearnOpenGL/LearnOpenGL/src/resources/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
#pragma endregion


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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
#pragma endregion

	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	ourShader.setInt("texture2", 1);

	// Render Loop
	while (!glfwWindowShouldClose(window)) {
		// Proccess Input
		proccessInput(window);
		
		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw Triangle
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		ourShader.setFloat("opacitySwitch", opacitySwitch);
		
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

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		if (opacitySwitch != 1.0f) {
			opacitySwitch += 0.01f;
		}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		if (opacitySwitch != -1.0f) {
			opacitySwitch -= 0.01f;
		}
}