#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
//#include <glm/detail/type_vec.hpp>
//#include <glm/detail/precision.hpp>

#include "VBO.hpp"
#include "VAO.hpp"
#include "IBO.hpp"
#include "TEX.h"
#include "FBO.h"

#include "Camera.h"
#include "Light.h"



class App final
{
	GLFWwindow* window = nullptr; // TODO: rename it properly

	VBO<glm::vec3, 3> m_vbo_pos_plane;
	IBO<GLushort> m_ibo_plane;

	glm::mat4 m_M_vertical_plane = glm::mat4(); // glm::mat4() is the identity matrix
	glm::mat4 m_M_horizontal_plane = glm::mat4();

	VAO m_vao_test_plane;
	GLint m_program_test_id;
	GLint m_M_test_id;

public:

	App(GLFWwindow* window) : window(window)
	{  
	}

	void init();
	void upDate();
	void render();
	void clean();
	void afterScreen();
};
