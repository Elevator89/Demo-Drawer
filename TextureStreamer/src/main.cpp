#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include <iomanip>

#include "ShaderUtil.h"
#include "TexUtil.h"
#include "Drawing/Topologies/CroppedTopology.h"
#include "Drawing/Topologies/ThorusTopology.h"
#include "Drawing/Colors/Color.h"
#include "Drawing/Colors/RandomColorGenerator.h"
#include "Drawing/Colors/SingleColorGenerator.h"
#include "Drawing/Colors/BouncingColorGenerator.h"
#include "Drawing/Colors/FilteredColorGenerator.h"
#include "Drawing/Colors/LowPassColorFilter.h"
#include "Drawing/Drawers/PopWithChanceDrawer.h"

// Function prototypes
std::string GetFileContents( const std::string& filename );
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void error_callback(int error, const char* description);

// Window dimensions
const GLuint Width = 1024, Height = 768;
unsigned int dotsPerStep = 100;

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(Width, Height, "Texture streaming demo", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);


	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, Width, Height);

	GLuint shaderProgram = LoadAndBuildShaderProgram("shaders/tex.vert", "shaders/tex.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions         // Texture Coords
		1.0f,  1.0f, 0.0f,   1.0f, 1.0f, // Top Right
		1.0f, -1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f  // Top Left
	};
	GLuint indices[] =    // Note that we start from 0!
	{
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO


	// Load and create a texture
	GLuint texture1;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	Field<uint32_t> field(Width, Height, 0x00000000);


	ITopology* topology = new ThorusTopology(Width, Height);

	IColorFilter* colorFilter = new LowPassColorFilter(6, 0.2f);

	//IColorGenerator* colorGenerator = new SingleColorGenerator((uint32_t)Color::White);
	//IColorGenerator* baseColorGenerator = new RandomColorGenerator();
	//IColorGenerator* colorGenerator = new FilteredColorGenerator(baseColorGenerator, colorFilter);
	IColorGenerator* colorGenerator = new BouncingColorGenerator(0.000001f, 0.000003f, 0.000011f);

	IDrawer* generator = new PopWithChanceDrawer(topology, colorGenerator, 0.6f, 0.75f);

	// Load, create texture and generate mipmaps
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, field.GetWidth(), field.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, field.GetData());
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	double time = glfwGetTime();

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		for(unsigned int i= 0; i< dotsPerStep; ++i)
			generator->Draw(field);

		// Render

		// Activate shader
		glUseProgram(shaderProgram);

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, field.GetWidth(), field.GetHeight(), GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, field.GetData());

		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);

		// Draw container
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);

		double newTime = glfwGetTime();
		double delta = newTime - time;
		time = newTime;

		std::cout << std::fixed << std::setprecision(2)
				  << "FPS = " << 1.0 / delta << '\r';
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	dotsPerStep = (unsigned int)(dotsPerStep * pow(2.0, yoffset));
	std::cout << "Dots per step = " << dotsPerStep << std::endl;
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}
