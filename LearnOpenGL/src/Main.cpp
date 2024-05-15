#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// DECLARATIONS
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void proccessInput(GLFWwindow* window);

// Configuration
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	// GLFW Initialization! Before most of GLFW can be used, it must be initialized.
	glfwInit();
	// GLFW Window Hints are "Configurations". the first argument of glfwWindowHit sets the option to configure, then the second sets the value of our option.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create an object for "window", it will take "width", "height", "name". | OPTIONAL: "monitor" to set fullscreen, NULL is windowed, and "share" to share resources, NULL is to not share.
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	// Null check on window, incase it fails to create.
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		// Terminate will kill all windows and end. (Will have to "reinitialize").
		glfwTerminate();
		return -1;
	}
	// Set the window object as glfws current context.
	glfwMakeContextCurrent(window);

	// Initialize GLAD before we can use any OpenGL functions.
	// Passing GLAD the function to load the OpenGL function pointers address, these are OS-Specific. glfwGetProcAddress defines the correct function based on OS.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Register it to tell GLFW to call this function on ever window resize.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// "Game Loop" or "Render Loop" Keeps the window from closing | Runs till GLFW is told to stop.
	// glfwWindowShouldClose checks if GLFW has been instructed to close.
	while (!glfwWindowShouldClose(window)) {
		// Proccess Input
		proccessInput(window);
		
		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Swap color buffer | Dispalys the "Front Buffer" when "Back Buffer" is compelet is swaps the back buffer to the front buffer negating any flickering. | Render then displayed, not rendering whilst being displayed.
		glfwSwapBuffers(window);
		// Checks for any events triggered (Keyboard, Mouse, etc).
		glfwPollEvents();
	}

	// After application close clean up GLFW
	glfwTerminate();
	return 0;
}

// Called everytime the window is resized which fills in the proper arguments.
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Defines the viewport location (lower left corner) then the width and height, which is equal to GLFWs dimentions.
	// I assume this is also how you can due a viewport like Unity, which instead is defined seperatly from the full window (Define its location and size).
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

}

// Proccesses input sent from user, and closes the window via exiting the while loop.
void proccessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}