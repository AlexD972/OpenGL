#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/texture.hpp>

using namespace glm;

int main(void)
{
	GLFWwindow *window;

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Playground", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//Pas de step9 donc on utilise le step8
	GLuint programID = LoadShaders("playground_steps/step8/StandardShading.vertexshader", "playground_steps/step8/StandardShading.fragmentshader");

	// Vertex data for a cube
	static const GLfloat g_vertex_buffer_data[] = {

		-1.0f, 1.0f, 0.2f,
		1.0f, 1.0f, 0.2f,
		-1.0f, -1.0f, 0.2f,

		1.0f, 1.0f, 0.2f,
		1.0f, -1.0f, 0.2f,
		-1.0f, -1.0f, 0.2f,

		-1.0f, 1.0f, -1.8f,
		1.0f, 1.0f, -1.8f,
		-1.0f, -1.0f, -1.8f,

		1.0f, 1.0f, -1.8f,
		1.0f, -1.0f, -1.8f,
		-1.0f, -1.0f, -1.8f,

		-1.0f, 1.0f, -1.8f,
		-1.0f, -1.0f, 0.2f,
		-1.0f, -1.0f, -1.8f,

		-1.0f, 1.0f, -1.8f,
		-1.0f, 1.0f, 0.2f,
		-1.0f, -1.0f, 0.2f,

		1.0f, 1.0f, 0.2f,
		1.0f, 1.0f, -1.8f,
		1.0f, -1.0f, 0.2f,

		1.0f, 1.0f, -1.8f,
		1.0f, -1.0f, -1.8f,
		1.0f, -1.0f, 0.2f,

		-1.0f, 1.0f, 0.2f,
		-1.0f, 1.0f, -1.8f,
		1.0f, 1.0f, -1.8f,

		-1.0f, 1.0f, 0.2f,
		1.0f, 1.0f, -1.8f,
		1.0f, 1.0f, 0.2f,

		-1.0f, -1.0f, 0.2f,
		1.0f, -1.0f, 0.2f,
		1.0f, -1.0f, -1.8f,

		-1.0f, -1.0f, 0.2f,
		1.0f, -1.0f, -1.8f,
		-1.0f, -1.0f, -1.8f};

	// One color for each vertex.
	static const GLfloat g_color_buffer_data[] = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f};

	// Normals
	static const GLfloat g_normal_buffer_data[] = {
		-1.0f, 1.0f, 0.2f,
		1.0f, 1.0f, 0.2f,
		-1.0f, -1.0f, 0.2f,

		1.0f, 1.0f, 0.2f,
		1.0f, -1.0f, 0.2f,
		-1.0f, -1.0f, 0.2f,

		-1.0f, 1.0f, -1.8f,
		1.0f, 1.0f, -1.8f,
		-1.0f, -1.0f, -1.8f,

		1.0f, 1.0f, -1.8f,
		1.0f, -1.0f, -1.8f,
		-1.0f, -1.0f, -1.8f,

		-1.0f, 1.0f, -1.8f,
		-1.0f, -1.0f, 0.2f,
		-1.0f, -1.0f, -1.8f,

		-1.0f, 1.0f, -1.8f,
		-1.0f, 1.0f, 0.2f,
		-1.0f, -1.0f, 0.2f,

		1.0f, 1.0f, 0.2f,
		1.0f, 1.0f, -1.8f,
		1.0f, -1.0f, 0.2f,

		1.0f, 1.0f, -1.8f,
		1.0f, -1.0f, -1.8f,
		1.0f, -1.0f, 0.2f,

		-1.0f, 1.0f, 0.2f,
		-1.0f, 1.0f, -1.8f,
		1.0f, 1.0f, -1.8f,

		-1.0f, 1.0f, 0.2f,
		1.0f, 1.0f, -1.8f,
		1.0f, 1.0f, 0.2f,

		-1.0f, -1.0f, 0.2f,
		1.0f, -1.0f, 0.2f,
		1.0f, -1.0f, -1.8f,

		-1.0f, -1.0f, 0.2f,
		1.0f, -1.0f, -1.8f,
		-1.0f, -1.0f, -1.8f};

	GLuint normalbuffer;
	GLuint vertexbuffer;
	GLuint colorbuffer;

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
	
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_normal_buffer_data),
				 g_normal_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	// Projection matrix : 45 degrees Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
	glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
	glm::vec3(0,0,0), // and looks at the origin
	glm::vec3(0,1,0) // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	glm::mat4 Model1 = glm::mat4(1.0f);
	glm::mat4 MVP;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float angle = 0.0f;


	glm::vec3 lightPos = glm::vec3(4, 4, 1);
	glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);



	do
	{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		angle += 3.14159f / 2.0f * deltaTime;
		float c = (float)cos(angle);
		float s = (float)sin(angle);
		Model1 = {c, 0.0f, s, 0.0f,
				 0.0f, 1.0f, 0.0f, 0.0f,
				 -s, 0.0f, c, 0.0f,
				 0.0f, 0.0f, 0.0f, 1.0f};
		// Model = glm::translate(Model, glm::vec3(0.0f, 0.001f, 0.0f));
		// Model = glm::scale(Model, glm::vec3(1.001f, 1.001f, 1.0f));
		// Model = glm::rotate(Model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		// Use our shader
		glUseProgram(programID);


		// 1rst attribute buffer: vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,		  // attribute 0.
			3,		  // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0,		  // stride
			(void *)0 // array buffer offset
		);
		
		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);

		glVertexAttribPointer(
			1, // attribute 1.
			// No particular reason for 1, but must match the layout in the shader.
			3,		  // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0,		  // stride
			(void *)0 // array buffer offset
		);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,		  // attribute 2.
			3,		  // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0,		  // stride
			(void *)0 // array buffer offset
		);

		MVP = Projection * View * Model1;
		


		// Draw the triangles
		glDrawArrays(GL_TRIANGLES, 0, sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]));

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model1[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Cleanup the buffer
		glDeleteBuffers(1, &vertexbuffer);

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
	glfwTerminate();

	return 0;
}