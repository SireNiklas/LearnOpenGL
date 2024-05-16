#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Function Declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void proccessInput(GLFWwindow* window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

#pragma region Shaders
#pragma region Vertext Shader Source
// Temp Vertex Shader
const char *vertextShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
				// Vec4(x, y, z, and w)
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";
#pragma endregion

#pragma region Fragment Shader Source
const char *fragment1ShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
				// Vec4(x, y, z, and w)
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

const char* fragment2ShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
// Vec4(x, y, z, and w)
"    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n";
#pragma endregion
#pragma endregion

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

#pragma region Build and Compile Shaders & Create Shader Program
	int success;
	char infoLog[512];
#pragma region Vertext Shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertextShaderSource, NULL);
	glCompileShader(vertexShader);

	// Error Handling
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion
#pragma region Fragment Shader
	unsigned int fragment1Shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment1Shader, 1, &fragment1ShaderSource, NULL);
	glCompileShader(fragment1Shader);

	// Error Handling
	glGetShaderiv(fragment1Shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment1Shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragment2Shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment2Shader, 1, &fragment2ShaderSource, NULL);
	glCompileShader(fragment2Shader);

	// Error Handling
	glGetShaderiv(fragment2Shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment2Shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion
#pragma region Shader Program
	unsigned int shader1Program = glCreateProgram();
	glAttachShader(shader1Program, vertexShader);
	glAttachShader(shader1Program, fragment1Shader);
	glLinkProgram(shader1Program);

	unsigned int shader2Program = glCreateProgram();
	glAttachShader(shader2Program, vertexShader);
	glAttachShader(shader2Program, fragment2Shader);
	glLinkProgram(shader2Program);

	// Error handling
	glGetProgramiv(shader2Program, GL_LINK_STATUS, &success);
	if (!success)
		glGetProgramInfoLog(shader2Program, 512, NULL, infoLog);
#pragma endregion
	// Clean up
	glDetachShader(shader1Program, vertexShader);
	glDetachShader(shader1Program, fragment1Shader);
	glDetachShader(shader2Program, vertexShader);
	glDetachShader(shader2Program, fragment2Shader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragment1Shader);
	glDeleteShader(fragment2Shader);
#pragma endregion

	// Triangle
	//float vertices[] = {
	//	-0.5f, 0.5f, 0.0f,	// Top Right
	//	 0.0f, -1.0f, 0.0f,	// Right
	//	-1.0f, -1.0f, 0.0f,	// Left

	//	 0.5f, 0.5f, 0.0f,	// Top
	//	 1.0f, -1.0f, 0.0f,	// Right
	//	 0.0f, -1.0f, 0.0f	// Left
	//};

	float Triangle1Vertices[] = {
	-0.5f, 0.5f, 0.0f,	// Top Right
	 0.0f, -1.0f, 0.0f,	// Right
	-1.0f, -1.0f, 0.0f,	// Left
	};

	float Triangle2Vertices[] = {
	 0.5f, 0.5f, 0.0f,	// Top
	 1.0f, -1.0f, 0.0f,	// Right
	 0.0f, -1.0f, 0.0f	// Left
	};

	// Square
	//float vertices[] = {
	//	 0.5f,  0.5f, 0.0f,	// top right
	//	 0.5f, -0.5f, 0.0f,	// bottom right
	//	-0.5f, -0.5f, 0.0f,	// bottom left
	//	-0.5f,  0.5f, 0.0f	// top left
	//};

	unsigned int indices[] = {
		0, 1, 3,	// First Triangle
		1, 2, 3		// Second Triangle
	};

#pragma region OpenGL Graphics Pipeline
	//// Create VBO & VAO
	//unsigned int VAO, VBO, EBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	//// Bind Vertext Array Object first, then bind and set buffers
	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glBindVertexArray(0);

	unsigned int Triangle1VBO, Triangle1VAO, Triangle2VBO, Triangle2VAO;
	// Triangle 1
	glGenVertexArrays(1, &Triangle1VAO);
	glGenBuffers(1, &Triangle1VBO);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle1VBO);
	glBindVertexArray(Triangle1VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle1Vertices), Triangle1Vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

	glGenVertexArrays(1, &Triangle2VAO);
	glGenBuffers(1, &Triangle2VBO);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle2VBO);
	glBindVertexArray(Triangle2VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle2Vertices), Triangle2Vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);


#pragma endregion

	// Render Loop
	while (!glfwWindowShouldClose(window)) {
		// Proccess Input
		proccessInput(window);
		
		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Drawn Triangle
		glUseProgram(shader1Program);
		glBindVertexArray(Triangle1VAO);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shader2Program);
		glBindVertexArray(Triangle2VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawArrays(GL_TRIANGLES, 3, 6);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		// Swap Buffers and Pull IO Events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// GL Cleanup | Optional
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &Triangle1VAO);
	glDeleteVertexArrays(1, &Triangle2VAO);
	glDeleteBuffers(1, &Triangle1VBO);
	glDeleteBuffers(1, &Triangle2VBO);

	glDeleteProgram(shader1Program);
	glDeleteProgram(shader2Program);

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
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}