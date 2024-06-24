#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math_vector.hpp>
#include <file.hpp>
#define NUMVERTS 6

static void RenderSceneCB();
static void CompileShaders();
static void CreateVertexBuffer();
static void AddShader(GLuint, const char*, GLenum);
static void ReadShaderFile(std::string, std::string&);
static ReadVertShader(std::string);
int main(int, char**);


std::string vfn = "./src/vertex.vs", ffn = "./src/fragment.fs";
GLuint VBO;
Vec3f vertices[NUMVERTS];

// Function that is called repeatedly in the main loop to update the model
static void IdleCB() {
	for (int i = 0; i < NUMVERTS; i++) {
		if (vertices[i].x >= 1.0f) {
			vertices[i].x = -1.0f;
		}
		else {
			vertices[i].x += 0.01f;
		}
	}
	glutPostRedisplay();
}

// Function that actually draws the screen, called repeatedly in the main loop during drawing phases
static void RenderSceneCB() {
	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind the gl array buffer to the global VBO object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Enable changing of position (attribute 0)
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// How to interpret arrays, where to start, how many to process
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

// Basic read function, get results from out_str
static void ReadShaderFile(std::string filename, std::string& out_str) {
	File file{ filename };
	file.read();
	out_str = file.contents;
}

// This process works for all types of shaders
static void AddShader(GLuint program, const char* contents, GLenum type) {
	GLuint shader_obj = glCreateShader(type);

	if (shader_obj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", type);
		exit(0);
	}
	const GLchar* p[1] = { contents };
	GLint lengths[1] = { strlen(contents) };

	// Get all source files and load them into shader obj
	glShaderSource(shader_obj, 1, p, lengths);

	// Compile all source files in shader obj
	glCompileShader(shader_obj);

	// Check that compilation was successful
	GLint success;
	glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &success);

	if (!success) {
		// Error log
		GLchar info_log[1024];
		glGetShaderInfoLog(shader_obj, 1024, NULL, info_log);
		fprintf(stderr, "Failed to compile shader type %d with following error: %s\n", type, info_log);
		exit(1);
	}

	// Attach fully compiled and check shader obj to program
	glAttachShader(program, shader_obj);
}

static void CompileShaders() {

	GLuint shader = glCreateProgram();
	
	if (shader == 0) {
		fprintf(stderr, "Error creating shader");
	}

	std::string fs, vs;
	
	ReadShaderFile(vfn, vs);

	if (vs.empty()) {
		fprintf(stderr, "Failed to read vertex shader\n");
		exit(1);
	}

	AddShader(shader, vs.c_str(), GL_VERTEX_SHADER);

	ReadShaderFile(ffn, fs);

	if (fs.empty()) {
		fprintf(stderr, "Failed to read fragment shader\n");
		exit(1);
	}
	
	AddShader(shader, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar log[1024] = {0};
	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (success == 0) {
		glGetProgramInfoLog(shader, sizeof(log), NULL, log);
		fprintf(stderr, "Failed to link shader: %s\n", log);
		exit(1);
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &success);
	if (success == 0) {
		glGetProgramInfoLog(shader, sizeof(log), NULL, log);
		fprintf(stderr, "Failed to validate shader: %s\n", log);
		exit(1);
	}
	
	glUseProgram(shader);
}


static void CreateVertexBuffer() {
	/*
	  Culling means that any triangle assembled
	  in a clockwise order will not be rendered
	  as it is facing the 'back' side, meaning
	  it is no longer visible
	*/
	glEnable(GL_CULL_FACE);

	/*
	  Changes which vertex order (CW, CCW) is
	  considered 'front facing'
	*/
	glFrontFace(GL_CW);

	/*
	  Tells OGL which face to cull, front or back
	*/
	glCullFace(GL_FRONT);


	
	vertices[0] = { -1.0f, -1.0f, 0.0f }; //left
	vertices[1] = {  .25f, -1.0f, 0.0f };//right
	vertices[2] = { -.25f,  1.0f, 0.0f }; //top
	vertices[3] = { -.25f,  1.0f, 0.0f }; //left
	vertices[4] = {  .25f, -1.0f, 0.0f }; //bottom
	vertices[5] = {  1.0f,  1.0f, 0.0f };  //right

	// Number of handles, pointer to GLuint array for x handles
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	int size[2] = { 720, 480 };
	glutInitWindowSize(size[0], size[1]);

	int pos[2] = { 0, 0 };
	glutInitWindowPosition(pos[0], pos[1]);

	int window = glutCreateWindow("Point Example");
	std::cout << "Window ID: " << window << std::endl;

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error '%s'\n", glewGetErrorString(res));
		return 1;
	}

	/*
	  Add vertices to vertex array to be drawn
	*/
	CreateVertexBuffer();

	CompileShaders();

	/*
	 Attaches RenderSceneCB (callback) as the function to call when the
	 display is set to be updated. This function must handle all the
	 necessary steps to actually render said display
	*/
	glutDisplayFunc(RenderSceneCB);




	//glutIdleFunc(IdleCB);
	/*
	 Needs to be the last function call of main
	 as glutMainLoop never returns
	*/
	glutMainLoop();

	return 0;
}