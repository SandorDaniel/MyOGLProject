//#define sd_debugger
#include "Debug.h" // TODO rename to sdd

#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
//#include <glm/detail/type_vec.hpp>
//#include <glm/detail/precision.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

#include "App.h"
#include "Shader.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "TEX.h"
#include "Camera.h"
#include "TangentSpace.hpp"



void App::init()
{
	#pragma region OBJ Loading and Compressing (Mass Storage -> RAM)

	std::vector<glm::vec3> v_pos_plane
	{
		glm::vec3(-2.0f, -2.0f, 0.0f),
		glm::vec3(+2.0f, -2.0f, 0.0f),
		glm::vec3(+2.0f, +2.0f, 0.0f),
		glm::vec3(-2.0f, +2.0f, 0.0f)
	};
	std::vector<GLushort> v_ind_plane
	{
		0, 1, 2, 0, 2, 3
	};

	#pragma endregion

	#pragma region OBJ Loading (RAM -> VRAM)

	m_vbo_pos_plane.load(v_pos_plane);
	m_ibo_plane.load(v_ind_plane);
	m_vao_test_plane.attach(m_ibo_plane);

	#pragma endregion

	#pragma region GPU-Side-Program SetUp (loading and compiling sahders, setting up uniform variables)

	m_vao_test_plane.attach(m_vbo_pos_plane);
	//m_vao_test_plane.attach(m_ibo_plane);

	// Create and compile our GLSL program from the shaders
	m_program_test_id = LoadShaders(
		std::vector<const char*>{"F:/Users/DELL/Documents/MyOGLProject/playground/VS.vertexshader"},
		std::vector<const char*>{"F:/Users/DELL/Documents/MyOGLProject/playground/FS.fragmentshader"});

	// Get a handle for our uniform variables
	// Only during the initialisation
	m_M_test_id = glGetUniformLocation(m_program_test_id, "M");
	m_V_test_id = glGetUniformLocation(m_program_test_id, "V");
	m_P_test_id = glGetUniformLocation(m_program_test_id, "P");



	#pragma endregion
}


void App::upDate()
{
	#pragma region INPUT UpDate

	for (auto it : InPut::KeyBoard::getActiveKeys())
	{
		if (glfwGetKey(window, it.first) == GLFW_PRESS)
		{
			it.second.release();
			it.second.press();
		}
	}

	#pragma endregion

	//camera.upDate(window);

	#pragma region MODEL-TRANSFORMATIONS UpDate

	//glm::mat4 S = glm::scale(glm::mat4(), glm::vec3(2.0f, 1.0f, 1.0f));
	//glm::mat4 R = glm::rotate(glm::mat4(), glm::radians<float>(45), glm::vec3(0.0f, 0.0f, 1.0f));
	//glm::mat4 T = glm::translate(glm::mat4(), glm::vec3(2.0f, 2.0f, 0.0f));

	//M = T * R * S;

	m_M_vertical_plane =
		glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -2.0f));

	m_M_horizontal_plane =
		glm::translate(glm::mat4(), glm::vec3(0.0f, -2.0f, 0.0f)) *
		glm::rotate(glm::mat4(), glm::radians<float>(-90), glm::vec3(1.0f, 0.0f, 0.0f));

	#pragma endregion
}


void App::render()
{
	#pragma region standard rendering

	glm::mat4 V = glm::lookAt(
		glm::vec3(0, 0, 5),           // Camera is here
		glm::vec3(0, 0, 0), // and looks here : at the same position, plus "direction"
		glm::vec3(0, 1, 0)                  // Head is up (set to 0,-1,0 to look upside-down)
	);
	int win_width, win_height;
	glfwGetWindowSize(window, &win_width, &win_height);
	glm::mat4 P = glm::perspective(
		glm::radians<float>(45.0f),
		static_cast<float>(win_width) / static_cast<float>(win_height),
		0.1f, 100.0f);
	//V = getView(m_camera);
	//P = getPerspectiveProj(m_camera);

	glUseProgram(m_program_test_id);
	
	m_vao_test_plane.bind();

	glUniformMatrix4fv(m_M_test_id, 1, GL_FALSE, &m_M_horizontal_plane[0][0]); // DSA version: glProgramUniformMatrix4fv(m_programID, m_MID, 1, GL_FALSE, &m_M[0][0]);
	glUniformMatrix4fv(m_V_test_id, 1, GL_FALSE, &V[0][0]); // DSA version: glProgramUniformMatrix4fv(m_programID, m_VID, 1, GL_FALSE, &V[0][0]);
	glUniformMatrix4fv(m_P_test_id, 1, GL_FALSE, &P[0][0]);

	// Draw the triangles !
	//glDrawArrays(GL_TRIANGLES, 0, m_vbo_pos.getElementCount()); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDrawElements(
		GL_TRIANGLES,                     // mode
		m_ibo_plane.getElementCount(),    // count
		GL_UNSIGNED_SHORT,                // type of indices
		(void*)0                          // element array buffer offset
	);

	glUniformMatrix4fv(m_M_test_id, 1, GL_FALSE, &m_M_vertical_plane[0][0]); // DSA version: glProgramUniformMatrix4fv(m_programID, m_MID, 1, GL_FALSE, &m_M2[0][0]);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,                     // mode
		m_ibo_plane.getElementCount(),    // count
		GL_UNSIGNED_SHORT,                // type of indices
		(void*)0                          // element array buffer offset
	);

	m_vao_test_plane.unBind();

	#pragma endregion
}


void App::afterScreen()
{
}


void App::clean()
{
}
