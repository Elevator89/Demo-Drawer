#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>

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
#include "Drawing/Drawers/PickerType.h"
#include "Drawing/Drawers/PointsTraverserType.h"
#include "Drawing/Drawers/RandomDrawer.h"
#include "Drawing/Drawers/QueuePopWithChanceDrawer.h"
#include "Drawing/Drawers/StackPopWithChanceDrawer.h"
#include "Drawing/Drawers/QueuePushWithChanceDrawer.h"
#include "Drawing/Drawers/StackPushWithChanceDrawer.h"
#include "Drawing/Drawers/IPointPicker.h"
#include "Drawing/Drawers/PointFromStartPicker.h"
#include "Drawing/Drawers/PointFromEndPicker.h"
#include "Drawing/Drawers/RandomPointPicker.h"
#include "Drawing/Drawers/ChanceBasedPointPicker.h"
#include "Drawing/Drawers/IPointPusher.h"
#include "Drawing/Drawers/PointToStartPusher.h"
#include "Drawing/Drawers/PointToEndPusher.h"
#include "Drawing/Drawers/RandomPointPusher.h"
#include "Drawing/Drawers/ChanceBasedPointPusher.h"
#include "Drawing/Drawers/IPointsTraverser.h"
#include "Drawing/Drawers/Neighbour4PointsTraverser.h"
#include "Drawing/Drawers/ChanceBasedPointsTraverser.h"
#include "Drawing/Drawers/PointsTraverserDrawer.h"

// Function prototypes
char* getCmdOption(char** begin, char** end, const std::string & option);
bool cmdOptionExists(char** begin, char** end, const std::string& option);

void switchPointsTraverser(PointsTraverserType traverserType);
IPointsTraverser* createPointsTraverser(PointsTraverserType traverserType);

void switchPicker(PickerType pickerType);
void switchPusher(PickerType pickerType);
IPointPicker* createPicker(PickerType pickerType);
IPointPusher* createPusher(PickerType pusherType);

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
PointsTraverserDrawer* m_drawer;

IPointPicker* m_pointPicker;
IPointPusher* m_pointPusher;
PickerType m_currentPickerType = PickerType::Random;
PickerType m_currentPusherType = PickerType::Random;

IPointsTraverser* m_pointsTraverser;
PointsTraverserType m_pointsTraverserType = PointsTraverserType::Neighbour4;


IColorGenerator* m_colorGenerator;

// The MAIN function, from here we start the application and run the game loop
int main(int argc, char * argv[])
{
	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = nullptr;

	if(cmdOptionExists(argv, argv+argc, "-f"))
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

	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);


	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, m_width, m_height);

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

	Field<uint32_t> field(m_width, m_height, 0x00000000);


	m_topology = new ThorusTopology(m_width, m_height);

	m_colorFilter = new LowPassColorFilter(6, 0.2f);

	//IColorGenerator* colorGenerator = new SingleColorGenerator((uint32_t)Color::White);
	//IColorGenerator* baseColorGenerator = new RandomColorGenerator();
	//IColorGenerator* colorGenerator = new FilteredColorGenerator(baseColorGenerator, colorFilter);
	m_colorGenerator = new BouncingColorGenerator(0.000001f, 0.000003f, 0.000011f);

	//IDrawer* generator = new QueuePushWithChanceDrawer(m_topology, colorGenerator, 0.5f, 0.95f);

	m_randomGenerator = new std::default_random_engine();

	m_pointPicker = createPicker(m_currentPickerType);
	m_pointPusher = createPusher(m_currentPusherType);
	m_pointsTraverser = createPointsTraverser(m_pointsTraverserType);

	m_drawer = new PointsTraverserDrawer(m_topology, m_pointPicker, m_pointPusher, m_pointsTraverser, m_colorGenerator, 0.9f, m_randomGenerator);

	// Load, create texture and generate mipmaps
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, field.GetWidth(), field.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, field.GetData());
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	double time = glfwGetTime();


	double dotsToDraw = 0.0f;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		dotsToDraw += m_dotsPerStep;

		if(dotsToDraw >= 1.0)
		{
			unsigned int dotsToDrawThisFrame = (unsigned int)dotsToDraw;
			dotsToDraw -= dotsToDrawThisFrame;

			for(unsigned int i= 0; i < dotsToDrawThisFrame; ++i)
				m_drawer->Draw(field);
		}

		// Render

		// Activate shader
		glUseProgram(shaderProgram);

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, field.GetWidth(), field.GetHeight(), GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, field.GetData());

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

char* getCmdOption(char** begin, char** end, const std::string & option)
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

	if(action == GLFW_PRESS)
	{
		if(key == GLFW_KEY_1)
			switchPicker(PickerType::Random);
		if(key == GLFW_KEY_2)
			switchPicker(PickerType::FromStart);
		if(key == GLFW_KEY_3)
			switchPicker(PickerType::FromEnd);
		if(key == GLFW_KEY_4)
			switchPicker(PickerType::RandomWithChance);
		if(key == GLFW_KEY_5)
			switchPicker(PickerType::FromStartWithChance);
		if(key == GLFW_KEY_6)
			switchPicker(PickerType::FromEndWithChance);

		if(key == GLFW_KEY_KP_1)
			switchPusher(PickerType::Random);
		if(key == GLFW_KEY_KP_2)
			switchPusher(PickerType::FromStart);
		if(key == GLFW_KEY_KP_3)
			switchPusher(PickerType::FromEnd);
		if(key == GLFW_KEY_KP_4)
			switchPusher(PickerType::RandomWithChance);
		if(key == GLFW_KEY_KP_5)
			switchPusher(PickerType::FromStartWithChance);
		if(key == GLFW_KEY_KP_6)
			switchPusher(PickerType::FromEndWithChance);

		if(key == GLFW_KEY_Q)
			switchPointsTraverser(PointsTraverserType::Neighbour4);
		if(key == GLFW_KEY_W)
			switchPointsTraverser(PointsTraverserType::Neighbour4WithChance);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	m_dotsPerStep = m_dotsPerStep * pow(2.0, yoffset);
	if(m_dotsPerStep < 1/60.0)
		m_dotsPerStep = 1/60.0;
	std::cout << "Dots per step = " << m_dotsPerStep << std::endl;
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void switchPointsTraverser(PointsTraverserType traverserType)
{
	if(m_pointsTraverserType == traverserType) return;
	m_pointsTraverserType = traverserType;

	delete m_pointsTraverser;
	m_pointsTraverser = createPointsTraverser(m_pointsTraverserType);
	m_drawer->SetPointsTraverser(m_pointsTraverser);
}

IPointsTraverser* createPointsTraverser(PointsTraverserType traverserType)
{
	IPointsTraverser* neighbour4PointsTraverser = new Neighbour4PointsTraverser();

	switch(traverserType)
	{
	case PointsTraverserType::Neighbour4WithChance:
		return new ChanceBasedPointsTraverser(neighbour4PointsTraverser, m_randomGenerator, 0.59f);
	case PointsTraverserType::Neighbour4:
	default:
		return neighbour4PointsTraverser;
	}
}

void switchPusher(PickerType pickerType)
{
	if(m_currentPusherType == pickerType) return;
	m_currentPusherType = pickerType;

	delete m_pointPusher;
	m_pointPusher = createPusher(m_currentPusherType);
	m_drawer->SetPointPusher(m_pointPusher);
}

void switchPicker(PickerType pickerType)
{
	if(m_currentPickerType == pickerType) return;
	m_currentPickerType = pickerType;

	delete m_pointPicker;
	m_pointPicker = createPicker(m_currentPickerType);
	m_drawer->SetPointPicker(m_pointPicker);
}

IPointPicker* createPicker(PickerType pickerType)
{
	switch(pickerType)
	{
	case PickerType::FromStart:
		return new PointFromStartPicker();
	case PickerType::FromEnd:
		return new PointFromEndPicker();
	case PickerType::Random:
		return new RandomPointPicker(m_randomGenerator);
	case PickerType::FromStartWithChance:
		return new ChanceBasedPointPicker(new PointFromStartPicker(), m_randomGenerator, 0.5f);
	case PickerType::FromEndWithChance:
		return new ChanceBasedPointPicker(new PointFromEndPicker(), m_randomGenerator, 0.5f);
	case PickerType::RandomWithChance:
		return new ChanceBasedPointPicker(new RandomPointPicker(m_randomGenerator), m_randomGenerator, 0.5f);
	default:
		return new RandomPointPicker(m_randomGenerator);
	}
}

IPointPusher* createPusher(PickerType pickerType)
{
	switch(pickerType)
	{
	case PickerType::FromStart:
		return new PointToStartPusher();
	case PickerType::FromEnd:
		return new PointToEndPusher();
	case PickerType::Random:
		return new RandomPointPusher(m_randomGenerator);
	case PickerType::FromStartWithChance:
		return new ChanceBasedPointPusher(new PointToStartPusher(), m_randomGenerator, 0.5f);
	case PickerType::FromEndWithChance:
		return new ChanceBasedPointPusher(new PointToEndPusher(), m_randomGenerator, 0.5f);
	case PickerType::RandomWithChance:
		return new ChanceBasedPointPusher(new RandomPointPusher(m_randomGenerator), m_randomGenerator, 0.5f);
	default:
		return new RandomPointPusher(m_randomGenerator);
	}
}
