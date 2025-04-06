#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "Color.h"
#include "ColorGeneration/BouncingColorGenerator.h"
#include "ColorGeneration/FilteredColorGenerator.h"
#include "ColorGeneration/LowPassColorFilter.h"
#include "ColorGeneration/RandomColorGenerator.h"
#include "ColorGeneration/SingleColorGenerator.h"
#include "PointTraversal/ChanceBasedPointsTraverser.h"
#include "PointTraversal/Neighbour4PointsTraverser.h"
#include "ChanceBasedDrawer.h"
#include "IPointsTraverser.h"
#include "ITopology.h"
#include "Filters.h"
#include "PointsTraverserType.h"
#include "IContainer.h"
#include "ContainerType.h"
#include "StackContainer.h"
#include "QueueContainer.h"
#include "Rendering/ShaderUtil.h"
#include "Rendering/TexUtil.h"
#include "Topologies/CroppedTopology.h"
#include "Topologies/ThorusTopology.h"

// Function prototypes
double clamp(double d, double min, double max);
char* getCmdOption(char** begin, char** end, const std::string& option);
bool cmdOptionExists(char** begin, char** end, const std::string& option);

void switchPointsTraverser(PointsTraverserType traverserType);
IPointsTraverser* createPointsTraverser(PointsTraverserType traverserType);

void switchContainer(ContainerType containerType);
IContainer* createContainer(ContainerType containerType);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void error_callback(int error, const char* description);

// Window dimensions
GLuint m_width = 1024;
GLuint m_height = 768;
double m_dotsPerStep = 100.0;

std::default_random_engine* m_randomGenerator;

ITopology* m_topology;
IColorFilter* m_colorFilter;
ChanceBasedDrawer* m_drawer;

ContainerType m_containerType = ContainerType::Stack;

IPointsTraverser* m_pointsTraverser;
PointsTraverserType m_pointsTraverserType = PointsTraverserType::Neighbour4;

IColorGenerator* m_colorGenerator;

// The MAIN function, from here we start the application and run the game loop
int main(int argc, char* argv[])
{
	// Start OpenGL context and OS window using the GLFW helper library.
	if (!glfwInit()) {
		std::cerr << "ERROR: could not start GLFW3" << std::endl;
		return 1;
	}

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = nullptr;

	if (cmdOptionExists(argv, argv + argc, "-f"))
	{
		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
		m_width = mode->width;
		m_height = mode->height;

		window = glfwCreateWindow(m_width, m_height, "Texture streaming demo", primaryMonitor, nullptr);
		glfwSetWindowMonitor(window, primaryMonitor, 0, 0, m_width, m_height, mode->refreshRate);
	}
	else
	{
		window = glfwCreateWindow(m_width, m_height, "Texture streaming demo", nullptr, nullptr);
	}

	if (!window) {
		std::cerr << "ERROR: Could not open window with GLFW3" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Start Glad, so we can call OpenGL functions.
	int version_glad = gladLoadGL(glfwGetProcAddress);
	if (version_glad == 0) {
		std::cerr << "ERROR: Failed to initialize OpenGL context" << std::endl;
		glfwTerminate();
		return 1;
	}
	std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version_glad) << "." << GLAD_VERSION_MINOR(version_glad) << std::endl;

	// Try to call some OpenGL functions, and print some more version info.
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version supported " << glGetString(GL_VERSION) << std::endl;

	// Define the viewport dimensions
	glViewport(0, 0, m_width, m_height);

	GLuint shaderProgram;
	try {
		shaderProgram = LoadAndBuildShaderProgram("shaders/tex.vert", "shaders/tex.frag");
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		glfwTerminate();
		return 1;
	}

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

	m_topology = new ThorusTopology(m_width, m_height);

	m_colorFilter = new LowPassColorFilter(6, 0.2f);

	//IColorGenerator* colorGenerator = new SingleColorGenerator((uint32_t)Color::White);
	//IColorGenerator* baseColorGenerator = new RandomColorGenerator();
	//IColorGenerator* colorGenerator = new FilteredColorGenerator(baseColorGenerator, colorFilter);
	m_colorGenerator = new BouncingColorGenerator(0.000001f, 0.000003f, 0.000011f);

	m_randomGenerator = new std::default_random_engine();

	m_pointsTraverser = createPointsTraverser(m_pointsTraverserType);

	//m_drawer = new QueuePushWithChanceDrawer(m_topology, m_colorGenerator, 0.5f, 0.95f);
	m_drawer = new ChanceBasedDrawer(m_topology, new StackContainer(), m_pointsTraverser, 0.7, 0.7, m_colorGenerator, 0.95f, m_randomGenerator);

	Field<uint32_t> backgroundField(m_width, m_height, 0x00000000);
	Field<uint32_t> foregroundField(m_width, m_height, 0x00000000);

	// Load and create a texture
	GLuint backgroundTexture = CreateTexture(backgroundField);
	GLuint foregroundTexture = CreateTexture(foregroundField);

	double time = glfwGetTime();
	double dotsToDraw = 0.0f;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			mouseX /= m_width;
			mouseY /= m_height;

			clamp(mouseX, 0.00001, 0.9999);
			clamp(mouseY, 0.00001, 0.9999);

			m_drawer->SetChanceToPick(mouseX);
			m_drawer->SetChanceToPush(mouseY);

			std::cout << std::fixed << std::setprecision(2)
				<< " X=" << mouseX
				<< " Y=" << mouseY
				<< '\r\n';
		}

		Darken(backgroundField, 0.99f);

		dotsToDraw += m_dotsPerStep;

		if (dotsToDraw >= 1.0)
		{
			unsigned int dotsToDrawThisFrame = (unsigned int)dotsToDraw;
			dotsToDraw -= dotsToDrawThisFrame;

			for (unsigned int i = 0; i < dotsToDrawThisFrame; ++i)
				m_drawer->Draw(backgroundField, foregroundField);
		}

		// Render
		ModifyTexture(backgroundTexture, backgroundField);
		ModifyTexture(foregroundTexture, foregroundField);

		// Activate shader
		glUseProgram(shaderProgram);

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, backgroundTexture);
		glUniform1i(glGetUniformLocation(shaderProgram, "backgroundTexture"), 0);

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, foregroundTexture);
		glUniform1i(glGetUniformLocation(shaderProgram, "foregroundTexture"), 1);

		// Draw container
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);

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

	delete m_drawer;
	delete m_colorGenerator;
	delete m_colorFilter;
	delete m_topology;

	exit(EXIT_SUCCESS);
}

double clamp(double d, double min, double max)
{
	const double t = d < min ? min : d;
	return t > max ? max : t;
}

char* getCmdOption(char** begin, char** end, const std::string& option)
{
	char** itr = std::find(begin, end, option);
	if (itr != end && ++itr != end)
	{
		return *itr;
	}
	return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
	return std::find(begin, end, option) != end;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_1)
			switchContainer(ContainerType::Stack);
		if (key == GLFW_KEY_2)
			switchContainer(ContainerType::Queue);
		if (key == GLFW_KEY_Q)
			switchPointsTraverser(PointsTraverserType::Neighbour4);
		if (key == GLFW_KEY_W)
			switchPointsTraverser(PointsTraverserType::Neighbour4WithChance);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	m_dotsPerStep = m_dotsPerStep * pow(2.0, yoffset);
	if (m_dotsPerStep < 1 / 60.0)
		m_dotsPerStep = 1 / 60.0;
	std::cout << "Dots per step = " << m_dotsPerStep << std::endl;
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void switchPointsTraverser(PointsTraverserType traverserType)
{
	if (m_pointsTraverserType == traverserType) return;
	m_pointsTraverserType = traverserType;

	delete m_pointsTraverser;
	m_pointsTraverser = createPointsTraverser(m_pointsTraverserType);
	m_drawer->SetPointsTraverser(m_pointsTraverser);
}

IPointsTraverser* createPointsTraverser(PointsTraverserType traverserType)
{
	IPointsTraverser* neighbour4PointsTraverser = new Neighbour4PointsTraverser();

	switch (traverserType)
	{
	case PointsTraverserType::Neighbour4WithChance:
		return new ChanceBasedPointsTraverser(neighbour4PointsTraverser, m_randomGenerator, 0.59f);
	case PointsTraverserType::Neighbour4:
	default:
		return neighbour4PointsTraverser;
	}
}

void switchContainer(ContainerType containerType)
{
	if (m_containerType == containerType) return;
	m_containerType = containerType;

	IContainer* oldContainer = m_drawer->GetContainer();
	IContainer* newContainer = createContainer(m_containerType);

	while (!oldContainer->IsEmpty())
		newContainer->Push(oldContainer->Pick());

	delete oldContainer;
	m_drawer->SetContainer(newContainer);
}

IContainer* createContainer(ContainerType containerType)
{
	switch (containerType)
	{
	case ContainerType::Stack:
		return new StackContainer();
	case ContainerType::Queue:
	default:
		return new QueueContainer();
	}
}

