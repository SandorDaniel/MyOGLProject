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

	VAO m_vao_cilinder;
	VBO<glm::vec, float, glm::qualifier::defaultp, 3> m_vbo_pos_cilinder;
	//VBO<glm::vec, float, glm::qualifier::defaultp, 3> m_vbo_nor;
	VBO<glm::vec, float, glm::qualifier::defaultp, 2> m_vbo_tex_cilinder;
	VBO<glm::vec, float, glm::qualifier::defaultp, 3> m_vbo_tg_cilinder;
	VBO<glm::vec, float, glm::qualifier::defaultp, 3> m_vbo_btg_cilinder;
	IBO<GLushort> m_ibo_cilinder;

	VAO m_vao_plane;
	VBO<glm::vec, float, glm::qualifier::defaultp, 3> m_vbo_pos_plane;
	VBO<glm::vec, float, glm::qualifier::defaultp, 2> m_vbo_tex_plane;
	VBO<glm::vec, float, glm::qualifier::defaultp, 3> m_vbo_tg_plane;
	VBO<glm::vec, float, glm::qualifier::defaultp, 3> m_vbo_btg_plane;
	IBO<GLushort> m_ibo_plane;
	
	TEX<ColorTexData> m_tex_matdiff_wall;
	TEX<ColorTexData> m_tex_matspec_wall;
	TEX<ColorTexData> m_tex_nor_wall;

	GLint m_program_nor_matlight_shadow_mapped_id;
	
	GLint m_M_nor_matlight_shadow_mapped_id;
	GLint m_V_nor_matlight_shadow_mapped_id;
	GLint m_P_nor_matlight_shadow_mapped_id;
	GLint m_cam_pos_nor_matlight_shadow_mapped_id;
	GLint m_tex_matdiff_nor_matlight_shadow_mapped_id;
	GLint m_tex_matspec_nor_matlight_shadow_mapped_id;
	GLint m_tex_norm_nor_matlight_shadow_mapped_id;
	GLint m_does_model_transformation_contain_nonuniform_scaling_nor_matlight_shadow_mapped_id;
	static constexpr GLint num_of_positional_lights = 2;
	GLint m_shadow_V_nor_matlight_shadow_mapped_id; //
	GLint m_tex_shadow_nor_matlight_shadow_mapped_id; //
	GLint m_shadow_P_nor_matlight_shadow_mapped_id; //

	PositionalLight  light_positional[num_of_positional_lights];
	DirectionalLight light_directional;

	glm::mat4 m_M_horizontal_cilinder = glm::mat4(1.0f); // glm::mat4(1.0f) is the identity matrix
	bool m_does_m_M_horizontal_cilinder_contain_nonuniform_scaling_horizontal_cilinder = false;
	glm::mat4 m_M_vertical_cilinder = glm::mat4(1.0f);
	bool m_does_m_M_vertical_cilinder_contain_nonuniform_scaling_horizontal_cilinder = false;

	glm::mat4 m_M_vertical_plane = glm::mat4(1.0f); // glm::mat4(1.0f) is the identity matrix
	bool m_does_m_M_vertical_plane_contain_nonuniform_scaling = false;
	glm::mat4 m_M_horizontal_plane = glm::mat4(1.0f);
	bool m_does_m_M_horizontal_plane_contain_nonuniform_scaling = false;

	InPutObserverCamera m_camera;

	TEX<DepthTexData> m_tex_depth[num_of_positional_lights];
	FBO fbo[num_of_positional_lights];
	GLint m_program_shadow_id;

	GLint m_shadow_M_shadow_id;
	GLint m_shadow_V_shadow_id;
	GLint m_shadow_P_shadow_id;

	glm::mat4 SV[num_of_positional_lights];
	glm::mat4 SP[num_of_positional_lights];

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
