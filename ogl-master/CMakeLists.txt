# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Tutorials)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()


include_directories(
	$ENV{GLFW_INCLUDE_DIR}
	external/glm-0.9.7.1/
	$ENV{GLEW_INCLUDE_DIR}
	.
)

link_directories($ENV{GLEW_LIBRARY})
link_directories($ENV{GLFW_LIBRARY})

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw3
	glew32s
)

#add_definitions(
	#-DTW_STATIC
	#-DTW_NO_LIB_PRAGMA
	#-DTW_NO_DIRECT3D
	#-DGLEW_STATIC
	#-D_CRT_SECURE_NO_WARNINGS
#)

# User playground
add_executable(
	playground 
	playground/App.cpp
	playground/InPuts.h
	playground/TEX.cpp
	playground/App.h
	playground/KeyBoard.cpp             
	playground/Aspects.cpp
	playground/KeyBoard.h
	playground/Shader.cpp
	playground/TEX.h
	playground/Aspects.hpp
	playground/Light.cpp
	playground/Shader.hpp
	playground/VAO.cpp
	playground/Camera.cpp
	playground/Light.h
	playground/VAO.hpp
	playground/Camera.h
	playground/Math.cpp
	playground/VBO.hpp
	playground/Debug.h
	playground/Math.h
	playground/wglext.h
	playground/FBO.cpp
	playground/Mouse.cpp
	playground/Window.cpp
	playground/FBO.h
	playground/Mouse.h
	playground/TangentSpace.cpp
	playground/Window.h
	playground/IBO.hpp
	playground/playground.cpp
	playground/TangentSpace.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/texture.cpp
	common/texture.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	playground/ShadowFragmentShader.fragmentshader
	playground/ShadowVertexShader.vertexshader
	playground/SimpleFragmentShader.fragmentshader
	playground/SimpleVertexShader.vertexshader
)
target_link_libraries(playground
	${ALL_LIBS}
)

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*shader$" )


#if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
#add_custom_command(
#   TARGET playground POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/playground${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/playground/"
#)
#
#elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )
#
#endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

