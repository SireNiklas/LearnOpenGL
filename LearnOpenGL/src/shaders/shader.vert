#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos; // Calculate world space coords
out vec3 Normal;

uniform mat4 model;			// Local
uniform mat4 view;			// Camera
uniform mat4 projection;	// World

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	FragPos = vec3(model * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(model))) * aNormal; // Have note covered Transpose or Inverse yet, don't fret (used for non-uniform scaling) | Expensive, calculate on CPU via unfiform to send to the shader
};