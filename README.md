# LearnOpenGL

## GLFW

> ###### Initialize GLFW
> ##### glfwInit();
<br>

### GLFW Window Configuration
> ###### GLFW Window Configuration, Allows us to tell GLFW how we want our window to act, what version of OpenGL we want, what profile for OpenGL | This way it sets up our window properly to handle it.<br><br>First argument defines the setting to change, the second argument changes the defined setting.
> ##### glfwWindowHint(int hint, int value);

<br>

### Creating and Destroying GLFW Window:
> ###### Create a window object | Arguments: (Width, Height, Title, Monitor to be fulscreen, Resource Sharing)
> > ##### glfwCreateWindow(width, height, "title", *monitor, *share);
> ###### Destroy window
> > ##### glfwTerminate();

```c++
GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
```
###### Typically you want to NULL check this object before use as it would be a catastrophic failure if not created.

<br>

### GLFW Context
> ###### Set the current window object as GLFW's current context.
> > ##### glfwMakContextCurrent(GLFWwindow *window);

<br>

### GLFW Render Loop
> ###### Render Loops keeps the window/viewport from closing. This will run until interoupt <br><br> This is where we Swap our render buffers, pull for events, proccess input, and draw things!
> > ##### glfwWindowShouldClose();
> ###### Swap Buffers will swap from the front buffer to the back buffer when complete. This gives a continous graphical rendering. <br><br> *This is known as 2D buffering, it negates artifacting such as flickering when drawing and render at the same time.
> > ##### glfwSwapBuffers(GLFWwindow *window);
> ###### Pull Events will continously poll for any events such as Keyboard, Mouse, etc.
> > ##### glfwPollEvents();

## GLAD
> ###### Initialize GLAD | Passing GLAD the function to load the OpenGL function pointers address, these are OS-Specific. glfwGetProcAddress defines the correct function based on OS.
> > ##### gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
```c++
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
}
```

## OpenGL Specification
### Vertex Buffer Objects
> ###### Generate named buffers (Names are integers) which store a blob of vertex data.
> ##### glGenBuffers(GLsizei n, GLuint *buffers)
> ###### Bind a buffer to a target. (Still dunno what the target is)
> > ##### glBindBuffer(GLenum target, GLunit buffer)
> ##### Fill the buffer with data.
> > ##### glBufferData(glBufferData(	GLenum 	target, GLsizeiptr 	size, const GLvoid * data, GLenum 	usage);)