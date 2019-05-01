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

	#pragma endregion
}


void App::render()
{
	#pragma region standard rendering

	glUseProgram(m_program_test_id);
	
	m_vao_test_plane.bind();

	// Draw the triangles !
	//glDrawArrays(GL_TRIANGLES, 0, m_vbo_pos.getElementCount()); // Starting from vertex 0; 3 vertices total -> 1 triangle
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
